#ifndef HTTP_UDP_UDPCLIENT_H
#define HTTP_UDP_UDPCLIENT_H

#include <string>


class UdpClient {
public:
    explicit UdpClient(std::string ip);

    virtual ~UdpClient();

    void sendRequest(std::string request) const;

    std::string getResponse() const;

private:
    std::string ip;

};




#endif //HTTP_UDP_UDPCLIENT_H
