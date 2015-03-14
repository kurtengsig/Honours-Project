#include "connection.h"
#include <QDebug>
int Connection::OpenListener(int port){
    int sd;
    struct sockaddr_in addr;

    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;
    if ( bind(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ){
        std::cout << "can't bind port";
        abort();
    }
    if ( listen(sd, 10) != 0 ){
        perror("Can't configure listening port");
        abort();
    }
    return sd;
}
SSL_CTX* Connection::InitServerCTX(void){
    const SSL_METHOD *method;
    SSL_CTX *ctx;           //new context
    OpenSSL_add_all_algorithms();
    SSL_load_error_strings();
    method = TLSv1_2_server_method();  // create new server-method instance
    ctx = SSL_CTX_new(method);   // create new context from method
    if ( ctx == NULL ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}
void Connection::LoadCertificates(SSL_CTX* ctx, char* CertFile, char* KeyFile){
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
void Connection::ShowCerts(SSL* ssl){
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
void Connection::Servlet(SSL* ssl, database* d) /* Serve the connection -- threadable */{
    char buf[1024];
    int sd, bytes;
    if ( SSL_accept(ssl) == -1 )     /* do SSL-protocol accept */
        ERR_print_errors_fp(stderr);
    else{
        //ShowCerts(ssl);        /* get any certificates */
        bytes = SSL_read(ssl, buf, sizeof(buf)); /* get request */
        if ( bytes > 0 ){
            buf[bytes] = 0;
            printf("Client msg: \"%s\"\n", buf);
            std::string inputString(buf);
            qDebug() << "Handling request for" << inputString.c_str();
            //Request handler stuff here

            RequestHandler h;
            std::string s = h.handle(inputString, d);
            qDebug() << s.c_str();
            SSL_write(ssl, s.c_str(), strlen(s.c_str())); /* send reply */
        }
        else
            ERR_print_errors_fp(stderr);
    }
    sd = SSL_get_fd(ssl);       /* get socket connection */
    SSL_free(ssl);         /* release SSL state */
    close(sd);          /* close connection */
}
void Connection::run(int portNum, database* d){
    SSL_CTX *ctx;
    int server;
    char *portnum;

    SSL_library_init();
    ctx = InitServerCTX();        /* initialize SSL */
    LoadCertificates(ctx, "certificate.crt", "privateKey.key"); /* load certs */
    server = OpenListener(portNum);    /* create server socket */
    while(1){
        struct sockaddr_in addr;
        socklen_t len = sizeof(addr);
        SSL *ssl;
        qDebug() << "Listening:";
        int client = accept(server, (struct sockaddr*)&addr, &len);  /* accept connection as usual */
        printf("Connection: %s:%d\n",inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
        ssl = SSL_new(ctx);              /* get new SSL state with context */
        SSL_set_fd(ssl, client);      /* set connection socket to SSL state */
        Servlet(ssl, d);         /* service connection */
    }
    close(server);          /* close server socket */
    qDebug() << "server socket closed";
    SSL_CTX_free(ctx);         /* release context */
    qDebug() << "context freed";
}
