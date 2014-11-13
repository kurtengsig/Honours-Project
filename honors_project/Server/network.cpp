#include "network.h"
#include <iostream>
network::network(){
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = 0;
    servaddr.sin_port = htons(5000);
    create();
    receiveMessage();
}
void network::create(){
    server = socket(AF_INET, SOCK_STREAM, 0);
    if (bind(server,(sockaddr*)&servaddr,sizeof(servaddr)) < 0){
        error="Failed to Bind";
    }
    std::cout << "listening..."<<std::endl;
    listen(server, 5000);
    clilen = sizeof(cliaddr);
    client = accept(server,(sockaddr*)&servaddr, &clilen);
    std::cout << "Netowrk connected" <<std::endl;
}
void network::sendMessage(std::string message){
    char data[255];
    strcpy(data, message.c_str());
    send(client, data, (size_t) strlen(data) + 1, 0);
}
std::string network::receiveMessage(){
    ssize_t n;
    char buffer[255];
    std::cout << "Netowrk listening" <<std::endl;
    n = read(client,&buffer,255);
    if (n<0){
        error="failed";
    }
    std::string out = buffer;
    std::cout << out <<std::endl;
    return out;
}
