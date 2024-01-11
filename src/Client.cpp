#include "../includes/Client.hpp"

Client::Client(int clientFd){
    this->_clientFd = clientFd;
    this->isRegistered = false;
}

int Client::getClientFd() {
    return this->_clientFd;
}

Channel *Client::getChannelByName(const std::string& name) {
	for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		if (it->second->getName() == name) {
			return it->second;
		}
	}
	return NULL;
}


Client::~Client(){
    
}