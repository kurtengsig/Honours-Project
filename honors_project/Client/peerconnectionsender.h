#ifndef PEERCONNECTIONSENDER_H
#define PEERCONNECTIONSENDER_H
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

class PeerConnectionSender{
public:
    PeerConnectionSender();
    void sendMessage(std::string ip, std::string port, std::string ac, std::string message);
    int OpenConnection(const char* hostname, int port);
    SSL_CTX* InitCTX(void);
    void ShowCerts(SSL* ssl);
    std::string run(std::string hostname, std::string portnum, std::string ac, std::string message);
};

#endif // PEERCONNECTIONSENDER_H
