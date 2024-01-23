/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:24:14 by charlie           #+#    #+#             */
/*   Updated: 2024/01/23 18:40:36 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	whoCmd(Client *client, const Command &command, Server *server)
{
	std::string	mask = command.args.empty() ? "" : command.args[0];
	
	if (command.args.empty())
	{
		std::map<int, Client*>				clients = server->getClients();
		std::map<int, Client*>::iterator	clientsIt;

		for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
		{
			Client							*currentClient = clientsIt->second;
			std::string						chanName;
			std::string						flags = "H";
			std::map<std::string, Channel*>	currentClientChannels = currentClient->getChannels();
			if (currentClientChannels.empty())
				chanName = "*";
			else
			{
				chanName = currentClientChannels.begin()->second->getName();
				chanUser	*cu = currentClientChannels.begin()->second->getClientByNick(client->nick);
				if (*cu->isOp)
					flags.append("@");
			}
			Server::sendToClient(client->fd, RPL_WHOREPLY(client->nick, chanName, \
				currentClient->user, currentClient->nick, flags, currentClient->real));
		}
	}
	else
	{
		bool	opOnly = command.args.size() > 1 && command.args[1] == "o";

		Channel	*channel = server->getChannelByName(command.args[0]);
		if (channel)
		{
			std::map<std::string, chanUser>				chanUsers = channel->getClients();
			std::map<std::string, chanUser>::iterator	chanUsersIt;

			for (chanUsersIt = chanUsers.begin(); chanUsersIt != chanUsers.end(); chanUsersIt++)
			{
				Client	*currentClient = chanUsersIt->second.client;
				if (opOnly && *chanUsersIt->second.isOp)
					continue ;
				if (channel->getClientByNick(client->nick))
				{
					std::string	flags = "H";
					if (*chanUsersIt->second.isOp)
						flags.append("@");
					Server::sendToClient(client->fd, RPL_WHOREPLY(client->nick, channel->getName(), \
						currentClient->user, currentClient->nick, flags, currentClient->real));
				}
			}
		}
		else
		{
			std::string							mask = command.args[0];
			std::map<int, Client*>				clients = server->getClients();
			std::map<int, Client*>::iterator	clientsIt;

			for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
			{
				Client *currentClient = clientsIt->second;
				if (mask == currentClient->nick || mask == currentClient->user || mask == currentClient->real || \
					mask == SERVER_NAME || mask == LOCALHOST_IP)
				{
					std::string						chanName;
					std::string						flags = "H";
					std::map<std::string, Channel*>	currentClientChannels = currentClient->getChannels();
					if (currentClientChannels.empty())
						chanName = "*";
					else
					{
						chanName = currentClientChannels.begin()->second->getName();
						chanUser	*cu = currentClientChannels.begin()->second->getClientByNick(client->nick);
						if (*cu->isOp)
							flags.append("@");
					}
					Server::sendToClient(client->fd, RPL_WHOREPLY(client->nick, chanName, \
						currentClient->user, currentClient->nick, flags, currentClient->real));
				}
			}
		}
	}
	Server::sendToClient(client->fd, RPL_ENDOFWHO(client->nick, mask));
}