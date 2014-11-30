#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class ServerConnection{
public:
    ServerConnection();
    std::string sendMessage(std::string m);

private:
    int status;
    struct addrinfo  host_info;
    struct addrinfo* host_info_list;
    int socketfd;
};

#endif // SERVERCONNECTION_H
