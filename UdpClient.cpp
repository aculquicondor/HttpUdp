#include "UdpClient.h"
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

UdpClient::UdpClient(std::string ip) : ip(ip) {
    this->port = "55533";

    memset(&this->addr, 0, sizeof(this->addr));
    this->addr.sin_family=AF_INET;
    this->addr.sin_addr.s_addr=htonl(INADDR_ANY);
    this->addr.sin_port=htons(0);

    if((this->sock=socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        return;
    }

    if(bind(this->sock,( struct sockaddr *) &this->addr, sizeof(this->addr)) < 0) {
        return;
    }

    inet_pton(AF_INET, this->ip.c_str() , &this->addr.sin_addr.s_addr);

    this->addr.sin_port = htons((uint16_t) std::stoi(this->port));
}

UdpClient::~UdpClient() {

}

void UdpClient::sendRequest(std::string request) const {
    std::cout<<"Working"<<std::endl;

    if(request.size() != sendto(this->sock, request.c_str(), request.size(), 0,
                                (struct sockaddr *)&this->addr, sizeof(this->addr))) {
        return;
    }
    std::cout<<"Working done"<<std::endl;

}

std::string UdpClient::getResponse() const {
    return "";
}


