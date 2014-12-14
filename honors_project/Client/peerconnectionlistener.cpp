#include "peerconnectionlistener.h"
#include <QDebug>
PeerConnectionListener::PeerConnectionListener(controller* c){
    cont = c;
}

int PeerConnectionListener::OpenListener(int port){
    int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ){
        qDebug() << "can't bind port";
        abort();
    }
    if ( listen(sd, 10) != 0 ){
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}
SSL_CTX* PeerConnectionListener::InitServerCTX(void){
    const SSL_METHOD *method;
    SSL_CTX *ctx;           //new context
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = SSLv3_server_method();  // create new server-method instance
    ctx = SSL_CTX_new(method);   // create new context from method
    if ( ctx == NULL ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}
void PeerConnectionListener::LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile){
    /* set the local certificate from CertFile */
    if ( SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0 ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* set the private key from KeyFile (may be the same as CertFile) */
    if ( SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0 ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    /* verify private key */
    if ( !SSL_CTX_check_private_key(ctx) ){
        fprintf(stderr, "Private key does not match the public certificate\n");
        abort();
    }
}
void PeerConnectionListener::ShowCerts(SSL* ssl){
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */
    if ( cert != NULL ){
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);
        X509_free(cert);
    }
    else
        printf("No certificates.\n");
}
void PeerConnectionListener::Servlet(SSL* ssl) /* Serve the connection -- threadable */{
    char buf[1024];
    int sd, bytes;
    if ( SSL_accept(ssl) == -1 )     /* do SSL-protocol accept */
        ERR_print_errors_fp(stderr);
    else{
        ShowCerts(ssl);        /* get any certificates */
        bytes = SSL_read(ssl, buf, sizeof(buf)); /* get request */
        if ( bytes > 0 ){
            buf[bytes] = 0;
            printf("Client msg: \"%s\"\n", buf);
            std::string inputString(buf);
            qDebug() << inputString.c_str();
//            cont->checkForConnection(inputString);
        }
        else
            ERR_print_errors_fp(stderr);
    }
    sd = SSL_get_fd(ssl);       /* get socket connection */
    SSL_free(ssl);         /* release SSL state */
    close(sd);          /* close connection */
}
void PeerConnectionListener::run(int portNum){
    SSL_CTX *ctx;
    int server;
    char *portnum;

    SSL_library_init();
    ctx = InitServerCTX();        /* initialize SSL */
    LoadCertificates(ctx, "cert.pem", "key.pem"); /* load certs */
    server = OpenListener(portNum);    /* create server socket */
    while(1){
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;
        qDebug() << "listening";
        int client = accept(server, (struct sockaddr*)&addr, &len);  /* accept connection as usual */
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        ssl = SSL_new(ctx);              /* get new SSL state with context */
        SSL_set_fd(ssl, client);      /* set connection socket to SSL state */
        Servlet(ssl);         /* service connection */

    }
    close(server);          /* close server socket */
    qDebug() << "server socket closed";
    SSL_CTX_free(ctx);         /* release context */
    qDebug() << "context freed";
}
