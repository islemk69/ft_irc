#include "Client.hpp"

Client::Client(int clientFd){
    this->_clientFd = clientFd;
}

int Client::getClientFd() {
    return this->_clientFd;
}

Client::~Client(){}