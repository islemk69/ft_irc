#include "../includes/Channel.hpp"

Channel::Channel(std::string name, Client *client, Server *server){
    this->_name = name;
    this->_server = server;
    (void) server;
    // this->_mode = "nt";
	// channelUser newClient;
	// newClient.client = client;
	// newClient.prefix = "@";
	// newClient.userMode = "o";
	// this->_mapClients[client->nickName] = newClient;

}
Channel::~Channel(){}


std::string     Channel::getName() const{
    return this->_name;
}