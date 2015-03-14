#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H
#include <iostream>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <sys/socket.h>
#include <resolv.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <fstream>

class ServerConnection{
public:
    int OpenConnection(const char* hostname, int port);
	SSL_CTX* InitCTX(void);
	void ShowCerts(SSL* ssl);
    std::string run(std::string hostname, std::string portnum, std::string message);
    std::string sendMessage(std::string);
private:
    void getServerInformation();
    std::string ip;
    std::string port;
};

#endif
void getServerInformation();
