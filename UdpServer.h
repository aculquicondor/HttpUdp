#ifndef HTTP_UDP_UDPSERVER_H
#define HTTP_UDP_UDPSERVER_H

#include <string>

struct RequestDescriptor {
    std::string ip, request;
};


class UdpServer {
public:
    explicit UdpServer();

    virtual ~UdpServer();

    RequestDescriptor getRequest();

    void sendResponse(std::string ip, std::string response);
};


#endif //HTTP_UDP_UDPSERVER_H
