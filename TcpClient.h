#ifndef HTTP_UDP_TCPCLIENT_H
#define HTTP_UDP_TCPCLIENT_H

#include <string>


class TcpClient {
public:
    explicit TcpClient();

    virtual ~TcpClient();

    void sendRequest(std::string request);

    std::string getResponse();

private:
    int socket_fd;

};


#endif //HTTP_UDP_TCPCLIENT_H
