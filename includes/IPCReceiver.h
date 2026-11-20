#pragma once
#include <string>
#include <mqueue.h>
#include "util.h"

class IPCReceiver
{
public:
    /************************************************************************************************************************
     * Description     : Constructor for IPCReceiver class.
     * Parameters      : 1) const std::string& queue_name => Name of the message queue
     * Return value    : None
     ************************************************************************************************************************/
    IPCReceiver(const std::string &msg_queue_name);

    /************************************************************************************************************************
     * Description     : Destructor for IPCReceiver class.
     * Parameters      : None
     * Return value    : None
     ************************************************************************************************************************/
    ~IPCReceiver();

    /************************************************************************************************************************
     * Description     : Create a message queue for the receiver.
     * Parameters      : None
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState createMessageQueue();

    /************************************************************************************************************************
     * Description     : Receive a message synchronously from the message queue.
     * Parameters      : 1) Message& message => Reference to a Message struct to store the received message
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState receiveSynchMessage(Message &message);

    /************************************************************************************************************************
     * Description     : Receive a message asynchronously from the message queue.
     * Parameters      : 1) Message& message => Reference to a Message struct to store the received message
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState receiveASynchMessage(Message &message);

private:
    mqd_t message_queue_fd; // Message queue descriptor
    std::string message_queue_name;
};
