 #include "network.h"

network::network(){
}
short network::create(){
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    getaddrinfo("localhost", NULL, NULL, &serverinfo);
    memcpy (&server, serverinfo->ai_addr, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);
    freeaddrinfo(serverinfo);
    if(connect(sockfd, (const struct sockaddr *) &server,sizeof(struct sockaddr_in))<0){
        return -1;
    }
    return 0;
}
void network::sendMessage(std::string message){
    char data[255];
    strcpy(data, message.c_str());
    send(sockfd, data, (size_t) strlen(data)+1, 0);
}
std::string network::receiveMessage(){
    char buffer[255];
    ssize_t n = read(sockfd, &buffer, 255);
    if(n<0){
        error = "failed to read";
    }
    std::string out = buffer;
    return out;
}
