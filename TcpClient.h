#ifndef HTTP_UDP_TCPCLIENT_H
#define HTTP_UDP_TCPCLIENT_H

#include <cstring>
#include <string>

#include <arpa/inet.h>
#include <unistd.h>

#include "utils.h"


class TcpClient {
public:
    explicit TcpClient();

    virtual ~TcpClient();

    void sendRequest(std::string request);

    std::string getResponse();

private:
    int sock;
    uint16_t server_port;
    struct sockaddr_in addr;
    std::string server_ip;
};


#endif //HTTP_UDP_TCPCLIENT_H
