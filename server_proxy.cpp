#include <thread>

#include "UdpServer.h"
#include "TcpClient.h"


class ServerProxy {
public:
    explicit ServerProxy() : server() {
    }

    void run() {
        while (true) {
            RequestDescriptor descriptor = server.getRequest();
            std::thread thread(&ServerProxy::serve, this, descriptor);
        }
    }

private:

    void serve(RequestDescriptor descriptor) {
        TcpClient client;
        client.sendRequest(descriptor.request);
        std::string response = client.getResponse();
        server.sendResponse(descriptor.ip, response);
    }

    UdpServer server;
};


int main() {
    ServerProxy proxy;
    proxy.run();
    return 0;
}