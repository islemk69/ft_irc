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

void            Channel::sendToAll(const std::string &msg){

}

void            Channel::eraseClient(const std::string & client){

}

// Client 		*Channel::getClientByNick(const std::string &nick){
//     for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
//         if (copyToUpper(nick) == copyToUpper(it->second->nickName)) {
//             return it->second;
//         }
//     }
// 	return NULL;
// }