#include "TcpClient.h"


TcpClient::TcpClient() {
    this->server_port = 8080;
    this->server_ip = "127.0.0.1";

    this->sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    memset(&this->addr, 0, sizeof(struct sockaddr_in));
    this->addr.sin_family = AF_INET;
    this->addr.sin_port = htons(this->server_port);
    inet_pton(AF_INET, this->server_ip.c_str(), &this->addr.sin_addr);

    connect(this->sock, (const struct sockaddr *)&this->addr, sizeof(struct sockaddr_in));
}

TcpClient::~TcpClient() {

}

void TcpClient::sendRequest(std::string request) {
    std::cout<<"Working"<<std::endl;

    if (send(this->sock, request.c_str(), request.size(), 0) < 0) {
        perror("Send failed : ");
        return;
    }

    std::cout<<"Working done"<<std::endl;
}

std::string TcpClient::getResponse() {
    std::string line;
    std::string response;

    do{
        line = this->getLine();
        response += line;
    }while(line != "\n" and line != "\r\n");

    return response;
}

std::string TcpClient::getLine() const {
    std::string line;
    char c;
    while (recv(this->sock, &c, 1, 0) > 0) {
        line.push_back(c);
        if (c == '\n')
            break;
    }
    return line;
}