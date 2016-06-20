#ifndef HTTP_UDP_TCPSERVER_H
#define HTTP_UDP_TCPSERVER_H

#include <string>


class TcpServer {
public:
    explicit TcpServer();

    virtual ~TcpServer();

    int listen() const;  // returns client_fd

    std::string getRequest(int clientFd) const;

    void sendResponse(int clientFd, std::string response) const;

private:
    int socket_fd;
};


#endif //HTTP_UDP_TCPSERVER_H
