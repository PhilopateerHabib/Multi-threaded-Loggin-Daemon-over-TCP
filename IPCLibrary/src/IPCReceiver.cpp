#include "IPCReceiver.h"
#include <iostream>

IPCReceiver::IPCReceiver(const std::string &msg_que_name) : message_queue_fd(-1), message_queue_name(msg_que_name) {}

IPCReceiver::~IPCReceiver()
{
}

SuccessState IPCReceiver::createMessageQueue()
{
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10; // Maximum number of messages in the queue
    attr.mq_msgsize = sizeof(Message);

    message_queue_fd = mq_open(message_queue_name.c_str(), O_CREAT | O_RDONLY, 0644, &attr);
    if (message_queue_fd == -1)
    {
        perror("mq_open");
        std::cout << "Can not open queue " << message_queue_name << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

SuccessState IPCReceiver::receiveSynchMessage(Message &message)
{
    // Check if the message queue is initialized
    if (message_queue_fd == -1)
    {
        std::cerr << "Message queue not initialized." << std::endl;
        return FAILURE;
    }

    ssize_t bytesReceived = mq_receive(message_queue_fd, reinterpret_cast<char *>(&message), sizeof(message), nullptr);
    if (bytesReceived == -1)
    {
        std::cerr << "Error receiving message." << std::endl;
        return FAILURE;
    }

    return SUCCESS;
}

SuccessState IPCReceiver::receiveASynchMessage(Message &message)
{

    if (message_queue_fd == -1)
    {
        std::cerr << "Message queue not initialized." << std::endl;
        return FAILURE;
    }

    ssize_t bytesReceived = mq_receive(message_queue_fd, reinterpret_cast<char *>(&message), sizeof(message), nullptr);
    if (bytesReceived == -1)
    {
        if (errno == EAGAIN)
        {
            // No messages available, return false without error
            return FAILURE;
        }
        else
        {
            std::cerr << "Error receiving message." << std::endl;
            return FAILURE;
        }
    }

    return SUCCESS;
}
