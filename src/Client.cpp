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

void	Client::addChannel(Channel *newChannel) {
	this->_channels[newChannel->getName()] = newChannel;
}

void	Client::eraseChannel(const std::string & target){
	this->_channels.erase(target);
}

void	Client::leaveChannel(Channel *channel, std::string cause){
	channel->sendToAll(RPL_CMD(this->nickName, this->userName, "PART", (channel->getName() + " " + cause)));
	this->eraseChannel(channel->getName());
	channel->eraseClient(this->nickName);
}

void	Client::leaveAll(){
	while (!this->_channels.empty())
		this->leaveChannel(this->_channels.begin()->second, "Starting leaving all channels");
}

Client::~Client(){
    
}