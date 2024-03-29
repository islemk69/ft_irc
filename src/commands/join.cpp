/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:35:55 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/30 14:40:55 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"
#include "../../includes/utils.hpp"

void	joinCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty())
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	if (command.args[0] == "0")
	{
		client->leaveAll(server);
		return ;
	}
	if (!client->isRegistered)
	{
		Server::sendToClient(client->fd, ERR_NOTREGISTERED("Client"));
		return ;
	}
	std::vector<std::string>	channels = ft_split(command.args[0], ",");
	std::vector<std::string>	keys;
	if (command.args.size() > 1)
		keys = ft_split(command.args[1], ",");
	std::vector<std::string>::iterator	keyIt = keys.begin();
	for(std::vector<std::string>::iterator chanIt = channels.begin(); chanIt != channels.end(); chanIt++)
	{
		if (chanIt->length() > CHANNAMEMAXLEN)
		{
			Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, *chanIt));
			continue ;
		}
		if (chanIt->find_first_of(" ,\a") != std::string::npos)
		{
			Server::sendToClient(client->fd, ERR_BADCHANMASK(*chanIt));
			continue ;
		}
		if (chanIt->find('#') != 0)
		{
			Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, *chanIt));
			continue ;
		}
		if (client->chansJoined() > CHANJOINMAX)
		{
			Server::sendToClient(client->fd, ERR_TOOMANYCHANNELS(client->nick, *chanIt));
			continue ;
		}
		Channel	*existingChannel = server->getChannelByName(*chanIt);
		if (!existingChannel)
		{
			Channel	*newChan = new Channel(*chanIt, client);

			if (keyIt != keys.end())
			{
				newChan->addMode('k');
				newChan->setKey(*keyIt);
			}
			server->addChannel(newChan);
			client->addChannel(newChan);

			Client		*bot = server->getClientFromFd(server->getBotFd());
			if (bot)
			{
				std::string	joinCmdStr = "JOIN " + *chanIt;
				if (keyIt != keys.end())
					joinCmdStr += " " + *keyIt;
				Command		jCmd(joinCmdStr);
				joinCmd(bot, jCmd, server);
			}
			
			Server::sendToClient(client->fd, RPL_CMD(client->nick, client->user, "JOIN", newChan->getName()));
			Server::sendToClient(client->fd, RPL_NAMREPLY(client->nick, "=", *chanIt, "@" + client->nick));
			if (bot)
				Server::sendToClient(client->fd, RPL_NAMREPLY("bot", "=", *chanIt, "bot"));
			Server::sendToClient(client->fd, RPL_ENDOFNAMES(client->nick, *chanIt));
			continue ;
		}
		else
		{
			if (existingChannel->hasMode('k') && (keyIt == keys.end() || *keyIt != existingChannel->getKey()))
			{
				Server::sendToClient(client->fd, ERR_BADCHANNELKEY(client->nick, *chanIt));
				continue ;
			}
			if (existingChannel->hasMode('i') && !existingChannel->isInvited(client->nick))
			{
				Server::sendToClient(client->fd, ERR_INVITEONLYCHAN(client->nick, *chanIt));
				continue ;
			}
			if (existingChannel->hasMode('l') && existingChannel->getNumberOfClients() == existingChannel->getClientLimit())
			{
				Server::sendToClient(client->fd, ERR_CHANNELISFULL(client->nick, *chanIt));
				continue ;
			}
			client->addChannel(existingChannel);
			existingChannel->addClient(client);
			existingChannel->sendToAll(RPL_CMD(client->nick, client->user, "JOIN", *chanIt));
			Server::sendToClient(client->fd, RPL_TOPIC(client->nick, existingChannel->getName(), existingChannel->getTopic()));
			
			std::map<std::string, chanUser>				clients = existingChannel->getClients();
			std::map<std::string, chanUser>::iterator	clientsIt;
			std::string									names;
			for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
			{
				if (clientsIt != clients.begin())
					names.append(" ");
				if (*clientsIt->second.isOp)
					names.append("@");
				names.append(clientsIt->first);
			}
			Server::sendToClient(client->fd, RPL_NAMREPLY(client->nick, "=", existingChannel->getName(), names));
			Server::sendToClient(client->fd, RPL_ENDOFNAMES(client->nick, existingChannel->getName()));
		}
		if (keyIt != keys.end())
			keyIt++;
	}
}