#ifndef HTTP_UDP_TCPCLIENT_H
#define HTTP_UDP_TCPCLIENT_H

#include <string>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>

class TcpClient {
public:
    explicit TcpClient();

    virtual ~TcpClient();

    void sendRequest(std::string request);

    std::string getResponse();

private:
    int sock;
    int server_port;
    struct sockaddr_in addr;
    std::string server_ip;
};


#endif //HTTP_UDP_TCPCLIENT_H
