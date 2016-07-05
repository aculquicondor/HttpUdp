#ifndef HTTP_UDP_UDPSERVER_H
#define HTTP_UDP_UDPSERVER_H

#include <cstring>
#include <unistd.h>
#include <sstream>
#include <iomanip>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


struct RequestDescriptor {
    sockaddr_in connection;
    std::string request;
};


class UdpServer {
public:
    explicit UdpServer();

    virtual ~UdpServer();

    RequestDescriptor getRequest();

    void sendResponse(sockaddr_in connection, std::string response);

private:

    int udp_socket;
    sockaddr_in remote_addr;
    socklen_t addr_len;

};


#endif //HTTP_UDP_UDPSERVER_H
