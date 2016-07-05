#include "UdpServer.h"


UdpServer::UdpServer() {

    sockaddr_in my_addr;

    udp_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    memset((char *)&my_addr, 0, sizeof my_addr);
    my_addr.sin_family = AF_INET;
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    my_addr.sin_port = htons(55533);

    addr_len = sizeof remote_addr;

    if (bind(udp_socket, (sockaddr *)&my_addr, sizeof my_addr) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

}

UdpServer::~UdpServer() {

}

RequestDescriptor UdpServer::getRequest() {

    RequestDescriptor request = RequestDescriptor();
    std::string buffer = std::string(10, '0');
    recvfrom(udp_socket, &buffer[0], buffer.size(), 0, (sockaddr *)&remote_addr, &addr_len);
    int message_length = stoi(buffer);
    buffer = std::string(message_length, '0');
    recvfrom(udp_socket, &buffer[0], buffer.size(), 0, (sockaddr *)&remote_addr, &addr_len);
    request.request = buffer;
    request.connection = remote_addr;

    return request;
}

std::string getResponseLength(std::string &response){

    std::stringstream stream;
    stream << std::setfill('0') << std::setw(10) << response.size();

    return stream.str();

}

void UdpServer::sendResponse(sockaddr_in connection, std::string response) {

    sendto(udp_socket, getResponseLength(response).c_str(), getResponseLength(response).size(), 0, (sockaddr *)&connection, addr_len);
    sendto(udp_socket, response.c_str(), response.size(), 0, (sockaddr *)&connection, addr_len);
}
