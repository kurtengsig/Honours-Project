#ifndef CONNECTION_H
#define CONNECTION_H
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "requesthandler.h"
#include "database.h"
class Connection
{
public:
    Connection(database* d);

public:
    int status;
    struct addrinfo  host_info;
    struct addrinfo* host_info_list;
};

#endif // CONNECTION_H
