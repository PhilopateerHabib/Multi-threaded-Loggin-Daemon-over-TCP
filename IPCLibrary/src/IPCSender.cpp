#include "IPCSender.h"
#include <iostream>

IPCSender::IPCSender(const std::string &msg_queue_name) : message_queue_fd(-1), message_queue_name(msg_queue_name) {}

IPCSender::~IPCSender()
{
    if (message_queue_fd != -1)
    {
        mq_close(message_queue_fd);
    }
}

SuccessState IPCSender::connectToMessageQueue()
{
    // Connect to an existing message queue
    message_queue_fd = mq_open(message_queue_name.c_str(), O_WRONLY);
    if (message_queue_fd == -1)
    {
        std::cerr << "Error connecting to message queue." << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}

SuccessState IPCSender::sendMessage(Message message)
{
    // Check if the message queue is connected
    if (message_queue_fd == -1)
    {
        std::cerr << "Message queue not connected." << std::endl;
        return FAILURE;
    }

    int result = mq_send(message_queue_fd, reinterpret_cast<const char *>(&message), sizeof(message), 0);
    if (result == -1)
    {
        std::cerr << "Error sending message." << std::endl;
        return FAILURE;
    }
    return SUCCESS;
}
