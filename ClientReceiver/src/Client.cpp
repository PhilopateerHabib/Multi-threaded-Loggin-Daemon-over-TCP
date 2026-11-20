#include "ClientReceiver.h"
#include <iostream>
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <IP address> <Port number>" << std::endl;
        return 1;
    }

    const char *serverIP = argv[1];
    int serverPort = std::atoi(argv[2]);

    ClientReceiver *client = ClientReceiver::getInstance();
    client->connectToServer(serverIP, serverPort);

    return 0;
}
