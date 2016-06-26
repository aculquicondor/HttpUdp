#include "TcpServer.h"


const uint16_t TcpServer::port = 8000;


TcpServer::TcpServer() {
    socketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (socketFd == -1) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in st_sock_addr;
    std::memset(&st_sock_addr, 0, sizeof st_sock_addr);
    st_sock_addr.sin_family = AF_INET;
    st_sock_addr.sin_port = htons(port);
    st_sock_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(socketFd, (const sockaddr *)&st_sock_addr, sizeof st_sock_addr) == -1) {
        perror("bind failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

    if (::listen(socketFd, 10) == -1) {
        perror("listen failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }

}

TcpServer::~TcpServer() {

}

int TcpServer::listen() const {
    int client_fd = accept(socketFd, NULL, NULL);
    if (client_fd < 0) {
        perror("accept failed");
        close(socketFd);
        exit(EXIT_FAILURE);
    }
    return client_fd;
}

std::string TcpServer::getRequest(int clientFd) const {
    std::string request, line;
    std::size_t contentLength = 0;
    do {
        line = getLine(clientFd);
        request += line;
        std::size_t colon = line.find(':');
        std::string header = line.substr(0, colon);
        if (lower(header) == "content-length") {
            std::stringstream ss(line.substr(colon+1));
            ss >> contentLength;
        }
    } while (line != "\n" and line != "\r\n");
    request += line;
    if (contentLength > 0) {
        line.resize(contentLength);
        read(clientFd, &line[0], contentLength);
    }
    return request;
}

void TcpServer::sendResponse(int clientFd, std::string response) const {
    write(clientFd, response.c_str(), response.size());
}


std::string TcpServer::getLine(int fd) const {
    std::string line;
    char c;
    while (read(fd, &c, 1) > 0) {
        line.push_back(c);
        if (c == '\n')
            break;
    }
    return line;
}


std::string TcpServer::lower(std::string str) const {
    for (char &c : str) {
        if (c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
    }
    return str;
}


