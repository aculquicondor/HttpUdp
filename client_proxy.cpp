#include <iostream>
#include <thread>

#include <netdb.h>
#include <signal.h>

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
            serve_thread.detach();
        }
    }

    int getServerSocketFd() const {
        return server.getSocketFd();
    }

private:
    void serve(int clientFd) {
        std::string request = server.getRequest(clientFd);
        std::string ip = getIp(request);

        if (ip.empty()) {
            close(clientFd);
            return;
        }

        UdpClient client(ip);

        client.sendRequest(request);
        std::string response = client.getResponse();
        server.sendResponse(clientFd, response);
        close(clientFd);
    }

    std::string getIp(std::string request) {
        std::size_t colon = request.find(':', request.find('\n')),
                enter = request.find('\n', colon);
        std::string host = request.substr(colon + 2, enter - colon - 2);
        if (host.back() == '\r')
            host.pop_back();

        if (host.front() >= '0' and host.front() <= '9')  // is IP
            return host;

        hostent *he;
        if ((he = gethostbyname(host.c_str())) == NULL) {
            herror("resolve failed");
            return "";
        }

        in_addr **addr_list = (in_addr **)he->h_addr_list;
        if (addr_list[0] == NULL)
            return "";

        return std::string(inet_ntoa(*addr_list[0]));
    }

    TcpServer server;
};

int socketFd;
void sig_handler(int sigNo) {
    shutdown(socketFd, SHUT_RDWR);
    close(socketFd);
    std::cerr << "Closing server socket" << std::endl;
    exit(0);
}


int main() {
    ClientProxy clientProxy;

    socketFd = clientProxy.getServerSocketFd();
    signal(SIGINT, sig_handler);
    signal(SIGTERM, sig_handler);

    clientProxy.run();
    return 1;
}