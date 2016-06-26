#ifndef HTTP_UDP_UDPCLIENT_H
#define HTTP_UDP_UDPCLIENT_H

#include <string>
#include <netinet/in.h>


class UdpClient {
public:
    explicit UdpClient(std::string ip);

    virtual ~UdpClient();

    void sendRequest(std::string request) const;

    std::string getResponse() const;

private:
    std::string ip;
    std::string port;
    int sock;
    struct sockaddr_in addr;
    // Port: 55533

};




#endif //HTTP_UDP_UDPCLIENT_H
