#pragma once

class ClientReceiver
{
private:
    int clientSocket;                // Socket descriptor for the client
    static ClientReceiver *instance; // Singleton instance

    ClientReceiver(); // Private constructor to enforce singleton pattern

    // Signal handler for Ctrl+C
    static void signalHandler(int signum);

    // Close the client socket
    void closeSocket();

public:
    /************************************************************************************************************************
     * Description     : Get the singleton instance of ClientReceiver class.
     * Parameters      : None
     * Return value    : ClientReceiver* => Pointer to the ClientReceiver instance
     ************************************************************************************************************************/
    static ClientReceiver *getInstance();

    /************************************************************************************************************************
     * Description     : Connect to the server at the specified IP address and port.
     * Parameters      : 1) const char* serverIP   => Pointer to the server IP address as a string
     *                   2) int serverPort         => Port number of the server
     * Return value    : None
     ************************************************************************************************************************/
    void connectToServer(const char *serverIP, int serverPort);

    /************************************************************************************************************************
     * Description     : Destructor to clean up resources.
     * Parameters      : None
     * Return value    : None
     ************************************************************************************************************************/
    ~ClientReceiver();
};
