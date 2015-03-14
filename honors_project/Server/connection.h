#ifndef CONNECTION_H
#define CONNECTION_H

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
#include "requesthandler.h"
#include "database.h"

class Connection{

public:
    int OpenListener(int port);
	SSL_CTX* InitServerCTX(void);
	void LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile);
	void ShowCerts(SSL* ssl);
    void Servlet(SSL* ssl, database *d);
    void run(int portNum, database* d);
};

#endif
