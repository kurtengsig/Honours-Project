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
#include <iostream>
class network
{
public:
    network();
    void sendMessage(std::string);
    std::string receiveMessage();
    short create();

private:
    int sockfd;
    std::string error;
    struct sockaddr_in server;
    struct addrinfo *serverinfo;
    ssize_t bytesreceived;
};

#endif // NETWORK_H
