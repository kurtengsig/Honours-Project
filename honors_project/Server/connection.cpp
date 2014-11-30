#include "connection.h"

Connection::Connection(database *d){
    /******************INITIALIZATION******************/
    memset(&host_info, 0, sizeof host_info);
    host_info.ai_family = AF_UNSPEC;
    host_info.ai_socktype = SOCK_STREAM;
    host_info.ai_flags = AI_PASSIVE;
    status = getaddrinfo("localhost", "8000", &host_info, &host_info_list);
    if(status != 0)
        std::cout << "getaddrinfo error" << gai_strerror(status);
    /******************\INITIALIZATION******************/

    /******************SOCKET CREATION******************/
    int socketfd;
    socketfd = socket(host_info_list->ai_family, host_info_list->ai_socktype, host_info_list->ai_protocol);
    if(socketfd == -1)
        std::cout << "socket error" << std::endl;
    /*****************\SOCKET CREATION*****************/

    /*****************BINDING*******************/
    int yes = 1;
    status = setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    status = bind(socketfd,host_info_list->ai_addr, host_info_list->ai_addrlen);
    if(status == -1)
        std::cout << "bind error" << std::endl;
    /*****************\BINDING***********************/

    /*****************LISTENING**********************/
    status = listen(socketfd, 25);
    if(status == -1)
        std::cout << "listen error" << std::endl;
    /*****************\LISTENING**********************/

    int new_sd;
    struct sockaddr_storage their_addr;
    socklen_t addr_size = sizeof(their_addr);
    new_sd = accept(socketfd, (struct sockaddr*)&their_addr, &addr_size);
    if(new_sd == -1){
        std::cout << "listen error" <<std::endl;
    }
    ssize_t bytes_recieved;
    char incoming_data_buffer[100];
    bytes_recieved = recv(new_sd, incoming_data_buffer, 1000, 0);
    if(bytes_recieved == 0)
        std::cout << "host shut down" << std::endl;
    if(bytes_recieved == -1)
        std::cout << "recieve error" << std::endl;
    incoming_data_buffer[bytes_recieved] = '\0';
    std::cout << "recieved: " << incoming_data_buffer << std::endl;

    std::string input = incoming_data_buffer;
    RequestHandler h;
    std::string s = h.handle(input, d);
    const char* msg = s.c_str();//(*output).c_str();
    std::cout << "Sending back: "<< msg << std::endl;
    int len;
    ssize_t bytes_sent;
    len = strlen(msg);
    bytes_sent = send(new_sd, msg, len, 0);
    close(new_sd);
    close(socketfd);
}
