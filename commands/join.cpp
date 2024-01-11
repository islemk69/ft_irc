/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:35:55 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/10 16:20:08 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../commands.hpp"

void	joinCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty())
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	if (command.args[0] == "0")
	{
		client->leaveAll();
		return ;
	}
	std::vector<std::string>	channels = Utils::split(command.args[0], ',');
	std::vector<std::string>	keys;
	if (command.args.size() > 1)
		keys = Utils::split(command.args[1], ',');
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
		if (*chanIt[0] != '#')
		{
			Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, *chanIt));
			continue ;
		}
		if (client->chansJoined() > CHANJOINMAX)
		{
			Server::sendToClient(client->fd, ERR_TOOMANYCHANNELS(client->nick, *chanIt));
			continue ;
		}
		Channel	*existingChan = server->getChannelByName(*chanIt);
		if (!existing)
		{
			Channel	*newChan = new Channel(*chanIt, client, server);

			if (keyIt != keys.end())
			{
				newChan->addMode('k');
				newChan->setKey(*keyIt);
			}
			server->addChannel(newChan);
			client->addChannel(newChan);
			Server::sendToClient(client->fd, RPL_CMD(client->nick, client->user, "JOIN", newChan->name));
			continue ;
		}
		else
		{
			if (existingChannel->hasMode('k') && (keyIt == keys.end() || *keyIt != existingChan->getKey()))
			{
				Server::sendToClient(client->fd, ERR_BADCHANNELKEY(client->nick, *chanIt));
				continue ;
			}
			if (existingChannel->hasMode('i') && !existingChannel->isInvited(client->nick))
			{
				Server::sendToClient(client->fd, ERR_INVITEONLYCHAN(client->nick, *chanIt))
				continue ;
			}
			if (existingChannel->hasMode('l') && existingChannel->getNumberOfClients() == existingChannel->getClientLimit())
			{
				Server::sendToClient(client->fd, ERR_CHANNELISFULL(client->nick, *chanIt));
				continue ;
			}
			client->addChannel(existingChannel);
			channel->addClient(client);
			channel->sendToAll(RPL_CMD(client->nick, client->user, "JOIN", *chanIt));
			Server::sendToClient(client->fd, RPL_TOPIC(client->nick, channel->name, channel->topic));
		}
		if (keyIt != keys.end())
			keyIt++;
	}
}