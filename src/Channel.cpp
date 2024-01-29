#include "../includes/Channel.hpp"

Channel::Channel(std::string name, Client *client){
    this->_name = name;
	this->_modes = "t";
	
	chanUser	newUser;
	newUser.client = client;
	newUser.isOp = new bool;
	*newUser.isOp = true;
	time(&newUser.joinTime);
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

std::string		Channel::getKey() const
{
	return this->_key;
}

std::string		Channel::getTopic() const
{
	return this->_topic;
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

void			Channel::addInvite(const std::string &client)
{
	this->_invited.push_back(client);
}

void			Channel::addClient(Client *client)
{
	chanUser	newUser;
	newUser.client = client;
	newUser.isOp = new bool;
	*newUser.isOp = false;
	time(&newUser.joinTime);
	this->_chanUsers[client->nick] = newUser;
}

void            Channel::eraseClient(const std::string & client)
{
	std::map<std::string, chanUser>::iterator	it = this->_chanUsers.find(client);
	if (it == this->_chanUsers.end())
		return ;
	delete it->second.isOp;
	this->_chanUsers.erase(client);
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

void			Channel::setTopic(const std::string &newTopic)
{
	this->_topic = newTopic;
}

void			Channel::setClientLimit(int limit)
{
	this->_clientLimit = limit;
}

void			Channel::updateClient(std::string oldNick, std::string newNick)
{
	chanUser									temp;
	std::map<std::string, chanUser>::iterator	it = this->_chanUsers.find(oldNick);

	if (it != this->_chanUsers.end())
	{
		temp = it->second;
		this->_chanUsers.erase(it);
		this->_chanUsers[newNick] = temp;
	}
}

chanUser		*Channel::getClientByNick(const std::string &nick)
{
	std::map<std::string, chanUser>::iterator	it;

	it = this->_chanUsers.find(nick);
	if (it == this->_chanUsers.end())
		return NULL;
	return &it->second;
}

std::map<std::string, chanUser>	Channel::getClients() const
{
	return this->_chanUsers;
}