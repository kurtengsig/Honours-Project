#include "peerconnectionsender.h"

PeerConnectionSender::PeerConnectionSender(){
}
int PeerConnectionSender::OpenConnection(const char *hostname, int port){
    int sd;
    struct hostent *host;
    struct sockaddr_in addr;

    if ( (host = gethostbyname(hostname)) == NULL ){
        perror(hostname);
        abort();
    }
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = *(long*)(host->h_addr);
    if ( connect(sd, (struct sockaddr*)&addr, sizeof(addr)) != 0 ){
        close(sd);
        perror(hostname);
        abort();
    }
    return sd;
}

SSL_CTX* PeerConnectionSender::InitCTX(void){
    const SSL_METHOD *method;
    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms();  /* Load cryptos, et.al. */
    SSL_load_error_strings();   /* Bring in and register error messages */
    method = SSLv3_client_method();  /* Create new client-method instance */
    ctx = SSL_CTX_new(method);   /* Create new context */
    if ( ctx == NULL ){
        ERR_print_errors_fp(stderr);
        abort();
    }
    return ctx;
}

void PeerConnectionSender::ShowCerts(SSL* ssl){
    X509 *cert;
    char *line;

    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */
    if ( cert != NULL ){
        printf("Server certificates:\n");
        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
        printf("Subject: %s\n", line);
        free(line);       /* free the malloc'ed string */
        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
        printf("Issuer: %s\n", line);
        free(line);       /* free the malloc'ed string */
        X509_free(cert);     /* free the malloc'ed certificate copy */
    }
    else
        printf("No certificates.\n");
}

std::string PeerConnectionSender::run(std::string hostname, std::string portnum, std::string message, std::string ac){ // might need to make this string a char *
    SSL_CTX *ctx;
    int server;
    SSL *ssl;
    char buf[1024];
    int bytes;
    int pn = atoi(portnum.c_str());
    if(hostname == "-1" || portnum == "-1")
        exit(-1);
    SSL_library_init();
    ctx = InitCTX();
    server = OpenConnection(hostname.c_str(), pn);
    ssl = SSL_new(ctx);      /* create new SSL connection state */
    SSL_set_fd(ssl, server);    /* attach the socket descriptor */
    if ( SSL_connect(ssl) == -1 )   /* perform the connection */
        ERR_print_errors_fp(stderr);
    else{
        printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
        ShowCerts(ssl);        /* get any certs */
        SSL_write(ssl, message.c_str(), strlen(message.c_str()));   /* encrypt & send message */
        SSL_free(ssl);        /* release connection state */
    }
    close(server);         /* close socket */
    SSL_CTX_free(ctx);        /* release context */
    return std::string(buf);
}
void PeerConnectionSender::sendMessage(std::string ip, std::string port, std::string ac, std::string message){
    run(ip, port, message, ac);
}
