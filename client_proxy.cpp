#include <thread>

#include "TcpServer.h"
#include "UdpClient.h"


class ClientProxy {
public:
    explicit ClientProxy() : server() {
    }

    virtual ~ClientProxy() {
    }

    void run() {
        while (true) {
            int client_fd = server.listen();
            std::thread serve_thread(&ClientProxy::serve, this, client_fd);
        }
    }

private:
    void serve(int clientFd) {
        std::string request = server.getRequest(clientFd);
        std::string ip = getIp(request);
        UdpClient client(ip);
        client.sendRequest(request);
        std::string response = client.getResponse();
        server.sendResponse(clientFd, response);
    }

    std::string getIp(std::string request) {
        return "";
    }

    TcpServer server;
};


int main() {
    UdpClient udp("127.0.0.1");
    udp.sendRequest("HOLA");
    return 1;
    ClientProxy clientProxy;
    clientProxy.run();
    return 0;
}