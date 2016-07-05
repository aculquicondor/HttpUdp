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
    std::size_t message_length = stoi(buffer);

    buffer.resize(message_length);
    recvfrom(udp_socket, &buffer[0], buffer.size(), 0, (sockaddr *)&remote_addr, &addr_len);
    request.request = buffer;
    request.connection = remote_addr;

    std::cout << "Received request: " << request.request.substr(0, 100) << "..." << std::endl << std::endl;
    return request;
}

void UdpServer::sendResponse(sockaddr_in connection, std::string response) {
    std::string first = to_10_digit_string(response.size());
    sendto(udp_socket, first.c_str(), first.size(), 0, (sockaddr *)&connection, addr_len);
    sendto(udp_socket, response.c_str(), response.size(), 0, (sockaddr *)&connection, addr_len);
    std::cout << "Sent response: " << response.substr(0, 100) << "..." << std::endl << std::endl;
}
