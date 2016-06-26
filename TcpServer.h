#ifndef HTTP_UDP_TCPSERVER_H
#define HTTP_UDP_TCPSERVER_H

#include <cstdlib>
#include <cstring>
#include <sstream>
#include <string>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>


class TcpServer {
public:
    explicit TcpServer();

    virtual ~TcpServer();

    int listen() const;  // returns client_fd

    std::string getRequest(int clientFd) const;

    void sendResponse(int clientFd, std::string response) const;

    int getSocketFd() const {
        return socketFd;
    }

private:
    std::string getLine(int fd) const;
    std::string lower(std::string str) const;

    int socketFd;
    static const uint16_t port;
};


#endif //HTTP_UDP_TCPSERVER_H
