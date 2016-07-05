#include "TcpClient.h"


TcpClient::TcpClient() {
    this->server_port = 5000;
    this->server_ip = "127.0.0.1";

    this->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&this->addr, 0, sizeof(struct sockaddr_in));
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(this->server_port);
    inet_pton(AF_INET, this->server_ip.c_str(), &this->addr.sin_addr);

    connect(this->sock, (const struct sockaddr *)&this->addr, sizeof(struct sockaddr_in));
}

TcpClient::~TcpClient() {
    shutdown(sock, SHUT_RDWR);
    close(sock);
}

void TcpClient::sendRequest(std::string request) {
    if (send(this->sock, request.c_str(), request.size(), 0) < 0) {
        perror("Send failed : ");
        return;
    }
}

std::string TcpClient::getResponse() {
    return httpRead(sock);
}

