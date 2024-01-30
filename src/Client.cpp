/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:27:17 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/30 17:19:26 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(int fd){
    this->fd = fd;
    this->isRegistered = false;
	this->hasPass = false;
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

void	Client::leaveChannel(Channel *channel, std::string cause, Server *server){
	int											nOp = 0;
	std::string									names;
	std::map<std::string, chanUser>				clients = channel->getClients();
	std::map<std::string, chanUser>::iterator	clientsIt;
	chanUser									*cu = channel->getClientByNick(this->nick);

	for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
	{
		if (*clientsIt->second.isOp)
			nOp++;
	}
	if (*cu->isOp && nOp == 1 && clients.size() > 2)
	{
		time_t		shortest;
		std::string	newOp;

		clientsIt = clients.begin();
		while (clientsIt->first == this->nick || clientsIt->first == "bot")
			clientsIt++;
		shortest = clientsIt->second.joinTime;
		newOp = clientsIt->first;
		for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
		{
			if (clientsIt->first == this->nick || clientsIt->first == "bot")
				continue ;
			if (clientsIt->second.joinTime < shortest)
			{
				shortest = clientsIt->second.joinTime;
				newOp = clientsIt->first;
			}
		}
		cu = channel->getClientByNick(newOp);
		*cu->isOp = true;
	}
	channel->sendToAll(RPL_CMD(this->nick, this->user, "PART", (channel->getName() + " " + cause)));
	this->eraseChannel(channel->getName());
	channel->eraseClient(this->nick);
	
	clients = channel->getClients();
	for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
	{
		if (clientsIt != clients.begin())
			names.append(" ");
		if (*clientsIt->second.isOp)
			names.append("@");
		names.append(clientsIt->first);
	}

	for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
	{
		Server::sendToClient(clientsIt->second.client->fd, \
			RPL_NAMREPLY(clientsIt->second.client->nick, "=", channel->getName(), names));
		Server::sendToClient(clientsIt->second.client->fd, \
			RPL_ENDOFNAMES(clientsIt->second.client->nick, channel->getName()));
	}

	if (channel->getClients().empty())
		server->rmChannel(channel);
}

void	Client::leaveAll(Server *server){
	while (!this->_channels.empty())
		this->leaveChannel(this->_channels.begin()->second, "Starting leaving all channels", server);
}

int		Client::chansJoined(){
	return this->_channels.size();
}

std::map<std::string, Channel*> Client::getChannels()const {
	return this->_channels;
}


Client::~Client(){
    
}
