#pragma once
#include <string>
#include <mqueue.h>
#include "util.h"

class IPCSender
{
public:
    /************************************************************************************************************************
     * Description     : Constructor for IPCSender class.
     * Parameters      : 1) const std::string& queue_name => Name of the message queue
     * Return value    : None
     ************************************************************************************************************************/
    IPCSender(const std::string &msg_queue_name);

    /************************************************************************************************************************
     * Description     : Destructor for IPCSender class.
     * Parameters      : None
     * Return value    : None
     ************************************************************************************************************************/
    ~IPCSender();

    /************************************************************************************************************************
     * Description     : Connect to an existing message queue.
     * Parameters      : None
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState connectToMessageQueue();

    /************************************************************************************************************************
     * Description     : Send a message through the message queue.
     * Parameters      : 1) Message message => Message to be sent
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState sendMessage(Message message);

private:
    mqd_t message_queue_fd;
    std::string message_queue_name;
};
