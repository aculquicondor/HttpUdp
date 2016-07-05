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
    std::string first = std::to_string(request.size());

    if (send(this->sock, first.c_str(), first.size(), 0) < 0) {
        perror("Send failed : ");
        return;
    }
    if (send(this->sock, request.c_str(), request.size(), 0) < 0) {
        perror("Send failed : ");
        return;
    }

    std::cout<<"Working done"<<std::endl;
}

std::string TcpClient::getResponse() {
    char buffer_size[10] = {0};
    if(recv(this->sock, buffer_size, 10, 0) < 0) {
        perror("Mismatch in number of bytes received");
    }

    std::string bs(buffer_size);

    int buff_size = std::stoi(bs);
    std::cout<<buff_size<<std::endl;
    std::string response(buff_size+1, 0);
    if(recv(this->sock, &response[0], buff_size, 0) < 0) {
        perror("Mismatch in number of bytes received");
    }
    std::cout<<response;
    return response;
}
