#include "TcpServer.h"


TcpServer::TcpServer() {

}

TcpServer::~TcpServer() {

}

int TcpServer::listen() const {
    return 0;
}

std::string TcpServer::getRequest(int clientFd) const {
    return "";
}

void TcpServer::sendResponse(int clientFd, std::string response) const {

}


