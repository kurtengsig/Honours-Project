#include "serverconnection.h"

ServerConnection::ServerConnection(){
    /******************INITIALIZATION******************/
    memset(&host_info, 0, sizeof host_info);
    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    status = getaddrinfo("localhost", "8000", &host_info, &host_info_list);
    if(status != 0)
        std::cout << "getaddrinfo error" << gai_strerror(status);
    /******************\INITIALIZATION******************/

    /******************SOCKET CREATION******************/
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
    if(socketfd == -1)
        std::cout << "socket error" << std::endl;
    /*****************\SOCKET CREATION*****************/

    /*****************CONNECTING***********************/
    std::cout << "Connecting to server" << std::endl;
    status = connect(socketfd,host_info_list->ai_addr, host_info_list->ai_addrlen);
    if(status == -1)
        std::cout << "connection error" << std::endl;
    /*****************\CONNECTING***********************/
}
std::string ServerConnection::sendMessage(std::string m){
    /***************SENDING A MESSAGE*******************/
    const char* msg = m.c_str();
    int len;
    ssize_t bytes_sent;
    len = strlen(msg);
    bytes_sent = send(socketfd, msg, len, 0);
    /***************\SENDING A MESSAGE*******************/

    /*************** RECIEVE A MESSAGE*******************/
    std::cout << "Waiting to receive message" << std::endl;
    ssize_t bytes_recieved;
    char incoming_data_buffer[1000];
    bytes_recieved = recv(socketfd, incoming_data_buffer, 100, 0);
    if(bytes_recieved == 0)
        std::cout << "host shut down" << std::endl;
    if(bytes_recieved == -1)
        std::cout << "Recieve error" << std::endl;
    incoming_data_buffer[bytes_recieved] = '\0';
    //std::cout << incoming_data_buffer << std::endl;
    /***************\RECIEVE A MESSAGE*******************/

    std::cout << "Closing socket" << std::endl;
    freeaddrinfo(host_info_list);
    close(socketfd);
    return std::string(incoming_data_buffer);
}
