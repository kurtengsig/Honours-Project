#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
class network
{
public:
    network();
    void create();
    void sendMessage(std::string);
    std::string receiveMessage();

private:
    int client, server;
    socklen_t clilen;
    std::string error;
    struct sockaddr_in servaddr, cliaddr;
};

#endif // NETWORK_H
