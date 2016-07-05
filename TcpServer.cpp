#include "TcpServer.h"
#include <iostream>

const uint16_t TcpServer::port = 8080;


TcpServer::TcpServer() {
    socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socketFd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in st_sock_addr;
    std::memset(&st_sock_addr, 0, sizeof st_sock_addr);
    st_sock_addr.sin_family = AF_INET;
    st_sock_addr.sin_port = htons(port);
    st_sock_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketFd, (const sockaddr *)&st_sock_addr, sizeof st_sock_addr) == -1) {
        perror("bind failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    if (::listen(socketFd, 10) == -1) {
        perror("listen failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

}

TcpServer::~TcpServer() {

}

int TcpServer::listen() const {
    int client_fd = accept(socketFd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    return client_fd;
}

#include <iostream>
std::string TcpServer::getRequest(int clientFd) const {
    std::string request = httpRead(clientFd);
    std::cout << request;
    return request;
}

void TcpServer::sendResponse(int clientFd, std::string response) const {
    std::cout<<"writing:"<<response<<std::endl;
    write(clientFd, response.c_str(), response.size());
    shutdown(clientFd, SHUT_RDWR);
    close(clientFd);
}
