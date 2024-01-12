#include "../includes/Channel.hpp"

Channel::Channel(std::string name, Client *client){
    this->_name = name;
	this->_modes = "t";
	
	chanUser	newUser;
	newUser.client = client;
	newUser.isOp = true;
	this->_chanUsers[client->nick] = newUser;
}

Channel::~Channel(){}


std::string     Channel::getName() const
{
    return this->_name;
}

std::string		Channel::getModes() const
{
	return this->_modes;
}

int				Channel::getNumberOfClients() const
{
	return this->_chanUsers.size();
}

int				Channel::getClientLimit() const
{
	return this->_clientLimit;
}

bool			Channel::hasMode(const char mode) const
{
	if (this->_modes.empty())
		return false;
	return (this->_modes.find(mode) != std::string::npos);
}

bool			Channel::isInvited(const std::string &client) const
{
	if (this->_invited.empty())
		return false;
	return (std::find(this->_invited.begin(), this->_invited.end(), client) != this->_invited.end());
}

void            Channel::sendToAll(const std::string &msg)
{
	if (this->_chanUsers.empty())
		return ;
	for (std::map<std::string, chanUser>::iterator it = this->_chanUsers.begin(); \
		it != this->_chanUsers.end(); it++)
	{
		Server::sendToClient(it->second.client->fd, msg);
	}
}

void            Channel::sendToAllButClient(int fd, const std::string &msg)
{
	if (this->_chanUsers.empty())
		return ;
	for (std::map<std::string, chanUser>::iterator it = this->_chanUsers.begin(); \
		it != this->_chanUsers.end(); it++)
	{
		if (it->second.client->fd != fd)
			Server::sendToClient(it->second.client->fd, msg);
	}
}

void			Channel::addClient(const Client *client)
{
	chanUser	newUser;
	newUser.client = client;
	newUser.isOp = false;
	this->_chanUsers[client->nick] = newUser;
}

void            Channel::eraseClient(const std::string & client)
{
	this->_chanUsers.erase(client->nick);
}

void			Channel::addMode(const char mode)
{
	if (this->_modes.find(mode) != std::string::npos)
		return ;
	this->_modes.push_back(mode);
}

void			Channel::rmMode(const char mode)
{
	std::size_t	found = this->_modes.find(mode);
	if (found == std::string::npos)
		return ;
	this->_modes.erase(found);
}

void			Channel::setKey(const std::string &key)
{
	this->_key = key;
}

void			Channel::setClientLimit(int limit)
{
	this->_clientLimit = limit;
}

chanUser		*Channel::getClientByNick(const std::string &nick)
{
	std::map<std::string, chanUser>::iterator	it;

	it = this->_chanUsers.find(nick);
	if (it == this->_chanUsers.end())
		return NULL;
	return &it->second;
}