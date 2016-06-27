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

    const char* buffer_char;
    RequestDescriptor request = RequestDescriptor();

    std::string buffer = std::string(buffer_char, 10);
    recvfrom(udp_socket, &buffer[0], buffer.size(), 0, (sockaddr *)&remote_addr, &addr_len);
    int message_length = stoi(buffer);
    buffer = std::string(buffer_char, message_length);
    recvfrom(udp_socket, &buffer[0], buffer.size(), 0, (sockaddr *)&remote_addr, &addr_len);
    request.request = buffer;
    request.ip = std::string(inet_ntoa(remote_addr.sin_addr));

    return request;
}

std::string getResponseLength(std::string &response){

    std::stringstream stream;
    stream << std::setfill('0') << std::setw(4) << response.size();

    return stream.str();

}

void UdpServer::sendResponse(std::string ip, std::string response) {

    sendto(udp_socket, getResponseLength(response).c_str(), getResponseLength(response).size(), 0, (sockaddr *)&remote_addr, addr_len);
    sendto(udp_socket, response.c_str(), response.size(), 0, (sockaddr *)&remote_addr, addr_len);
}
