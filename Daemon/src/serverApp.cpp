#include <iostream>
#include <thread>
#include <sstream>
#include "Server.h"
#include "util.h"
#include "IPCReceiver.h"
#include <vector>
#include <string.h>
#include <yaml-cpp/yaml.h>

int main()
{

    YAML::Node config = YAML::LoadFile("/etc/Daemon_Looger_config.yaml");
    int socket_port_num = config["Socket_Port_Number"].as<int>();

    Server *My_Server = &Server::getInstance();

    if (My_Server->createServerSocket() == FAILURE)
    {
        return 1;
    }
    if (My_Server->bindSocket(socket_port_num) == FAILURE)
    {
        return 1;
    }
    if (My_Server->listenSocket() == FAILURE)
    {
        return 1;
    }

    std::vector<std::thread> receiverThreads;
    int numInstances = config["Number_of_Applications"].as<int>();

    for (int i = 0; i < numInstances; ++i)
    {
        std::string appName = config["Instances"][i]["App_Name"].as<std::string>();
        std::string queueName = config["Instances"][i]["Queue_Name"].as<std::string>();
        std::string receiverType = config["Instances"][i]["Receiver_Type"].as<std::string>();

        bool isSynchronous = (receiverType == "synchronous");

        receiverThreads.emplace_back([&, queueName, appName, isSynchronous]()
                                     {
            IPCReceiver My_Receiver(queueName);
            My_Receiver.createMessageQueue();
            int result;
            Message my_msg;
            std::string message;

            while (true) {
                std::cout<<"waiting"<<std::endl;
                if (isSynchronous) {
                    if (My_Receiver.receiveSynchMessage(my_msg) == FAILURE) {
                        continue;
                    }
                } else {
                    // Handle asynchronous case
                    // ...
                }


                std::cout << my_msg.msg << std::endl;
                message = My_Server->saveLog("/home/philo/Capstone_Project/run_logs_philo.txt", "["+appName +"] " + my_msg.msg, my_msg.log_level);

                if (My_Server->getSocketClosingState()) {
                    My_Server->acceptClientConnection();
                }
                if (My_Server->sendResultToClient(message) == FAILURE) {
                    continue;
                }
            } });
    }

    // Join the threads when done
    for (auto &thread : receiverThreads)
    {
        thread.join();
    }

    My_Server->closeAll();
    return 0;
}
