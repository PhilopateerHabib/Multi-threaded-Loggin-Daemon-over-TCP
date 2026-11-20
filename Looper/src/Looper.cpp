#include <iostream>
#include <cstring>
#include "util.h"
#include "IPCSender.h"
#include <ctime>
#include <unistd.h>
Message my_msg;

void sendMyMessage(IPCSender *My_Sender, const char *msg, LogLevel log_level)
{
    strcpy(my_msg.msg, msg);
    my_msg.log_level = log_level;
    My_Sender->sendMessage(my_msg);
}

int main(int argc, char *argv[])
{
    IPCSender My_Sender = IPCSender("/Looper_Msg_Que");

    if (My_Sender.connectToMessageQueue() == FAILURE)
    {
        return 1;
    }

    sendMyMessage(&My_Sender, "Just connected to message queue", Info);
    sendMyMessage(&My_Sender, "Checking number of args", Info);

    if (argc != 2)
    {
        std::string argv_0(argv[0]);

        std::string err_msg = "Usage: " + argv_0 + " <operand1>";
        std::string full_msg = "Invalid input => " + err_msg;
        sendMyMessage(&My_Sender, full_msg.c_str(), Error);
        std::cout << full_msg << std::endl;
        return 1;
    }

    sendMyMessage(&My_Sender, "Start parsing the input", Info);

    int operand1 = std::stoi(argv[1]);

    sendMyMessage(&My_Sender, "Finish parsing the input", Info);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int i = 0; i < operand1; ++i)
    {
        int random_number = std::rand();
        std::cout << "Random Number: " << random_number << std::endl;

        int random_delay = std::rand() % 451 + 50;
        std::string rand_num = "This is random number " + std::to_string(random_number);
        sendMyMessage(&My_Sender, rand_num.c_str(), Info);

        usleep(random_delay * 1000);
    }
    return 0;
}
