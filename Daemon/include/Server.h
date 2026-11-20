#pragma once

#include <mqueue.h>
#include <iostream>
#include "util.h"

class Server
{
public:
    static Server &getInstance();

    /************************************************************************************************************************
     * Description     : Create a server socket.
     * Parameters      : None
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState createServerSocket();

    /************************************************************************************************************************
     * Description     : Bind a socket to a port.
     * Parameters      : 1) const int socket_port_num => Port number to bind the socket to
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState bindSocket(const int socket_port_num);

    /************************************************************************************************************************
     * Description     : Listen for incoming connections on the server socket.
     * Parameters      : None
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState listenSocket();

    /************************************************************************************************************************
     * Description     : Save log message to a file.
     * Parameters      : 1) const char *file_name   => Name of the log file
     *                   2) std::string message    => Message to be logged
     *                   3) LogLevel log_level     => Severity level of the log message
     * Return value    : std::string => Formatted log message
     ************************************************************************************************************************/
    std::string saveLog(const char *file_name, std::string message, LogLevel log_level);

    /************************************************************************************************************************
     * Description     : Accept client connection.
     * Parameters      : None
     * Return value    : None
     ************************************************************************************************************************/
    void acceptClientConnection();

    /************************************************************************************************************************
     * Description     : Send result to the client.
     * Parameters      : 1) std::string message => Message to be sent
     * Return value    : SuccessState enum indicating the result of the operation
     ************************************************************************************************************************/
    SuccessState sendResultToClient(std::string message);

    /************************************************************************************************************************
     * Description     : Get the socket closing state.
     * Parameters      : None
     * Return value    : bool => Whether the socket is closed or not
     ************************************************************************************************************************/
    bool getSocketClosingState();

    /************************************************************************************************************************
     * Description     : Get the server socket file descriptor.
     * Parameters      : None
     * Return value    : int => Server socket file descriptor
     ************************************************************************************************************************/
    int getServerSocketFd();

    /************************************************************************************************************************
     * Description     : Get the client socket file descriptor.
     * Parameters      : None
     * Return value    : int => Client socket file descriptor
     ************************************************************************************************************************/
    int getClientSocketFd();

    /************************************************************************************************************************
     * Description     : Close all resources.
     * Parameters      : None
     * Return value    : None
     ************************************************************************************************************************/
    void closeAll();

private:
    Server();                                   // Private constructor to enforce singleton pattern
    Server(const Server &) = delete;            // Disable copy constructor
    Server &operator=(const Server &) = delete; // Disable assignment operator

    /************************************************************************************************************************
     * Description     : Signal handler for termination signals.
     * Parameters      : 1) int signum => Signal number
     * Return value    : None
     ************************************************************************************************************************/
    static void signalHandler(int signum);

    /************************************************************************************************************************
     * Description     : Write log message to a file.
     * Parameters      : 1) const std::string &filename  => Name of the log file
     *                   2) const std::string &message   => Message to be logged
     * Return value    : std::string => Formatted log message
     ************************************************************************************************************************/
    static std::string writeLogToFile(const std::string &filename, const std::string &message, LogLevel severity);

    // Private data members
    static int server_socket_fd;
    static int client_socket_fd;
    static bool is_closed_socket;
};
