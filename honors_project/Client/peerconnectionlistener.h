#ifndef PEERCONNECTIONLISTENER_H
#define PEERCONNECTIONLISTENER_H
#include "controller.h"
#include <errno.h>
#include <unistd.h>
#include <malloc.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <resolv.h>
#include "openssl/ssl.h"
#include "openssl/err.h"

class PeerConnectionListener{

public:
    PeerConnectionListener(controller * c);
    int OpenListener(int port);
    SSL_CTX* InitServerCTX(void);
    void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile);
    void ShowCerts(SSL* ssl);
    void Servlet(SSL* ssl);
    void run(int portNum);

private:
    controller* cont;
};

#endif // PEERCONNECTIONLISTENER_H

