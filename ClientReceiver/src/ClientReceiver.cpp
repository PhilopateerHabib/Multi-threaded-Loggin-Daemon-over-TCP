#include "ClientReceiver.h"
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>

ClientReceiver *ClientReceiver::instance = nullptr;

ClientReceiver::ClientReceiver() : clientSocket(-1)
{
    // Private constructor to enforce singleton pattern
    // Set up signal handler for Ctrl+C
    signal(SIGINT, signalHandler);
}

void ClientReceiver::signalHandler(int signum)
{
    std::cout << "\nClosing client socket..." << std::endl;
    getInstance()->closeSocket();
    exit(signum);
}

void ClientReceiver::closeSocket()
{
    if (clientSocket != -1)
    {
        close(clientSocket);
        clientSocket = -1;
    }
}

ClientReceiver *ClientReceiver::getInstance()
{
    if (!instance)
    {
        instance = new ClientReceiver();
    }
    return instance;
}

void ClientReceiver::connectToServer(const char *serverIP, int serverPort)
{
    if (clientSocket != -1)
    {
        std::cerr << "Client socket already connected" << std::endl;
        return;
    }

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        std::cerr << "Error creating socket" << std::endl;
        return;
    }

    // Connect to server
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(serverPort);
    if (inet_pton(AF_INET, serverIP, &serverAddr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address or address not supported" << std::endl;
        closeSocket();
        return;
    }

    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == -1)
    {
        std::cerr << "Error connecting to server" << std::endl;
        closeSocket();
        return;
    }

    // Receive and print data
    char buffer[1024];
    while (true)
    {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0)
        {
            std::cout << "Server disconnected" << std::endl;
            signalHandler(2);
            break;
        }
        buffer[bytesReceived] = '\0';
        std::cout << buffer << std::endl;
    }
}

ClientReceiver::~ClientReceiver()
{
    closeSocket();
}
