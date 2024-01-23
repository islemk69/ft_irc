/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:10:54 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/23 18:43:47 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	partCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty())
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	std::string							reason = command.args.size() > 1 ? command.args[1] : "";
	std::vector<std::string>			channels = ft_split(command.args[0], ",");
	std::vector<std::string>::iterator	chanIt;

	for (chanIt = channels.begin(); chanIt != channels.end(); chanIt++)
	{
		Channel	*channel = server->getChannelByName(*chanIt);
		if (!channel)
		{
			Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, *chanIt));
			return ;
		}
		chanUser	*cu = channel->getClientByNick(client->nick);
		if (!cu)
		{
			Server::sendToClient(client->fd, ERR_NOTONCHANNEL(client->nick, *chanIt));
			return ;
		}
		int											nOp = 0;
		std::map<std::string, chanUser>				clients = channel->getClients();
		std::map<std::string, chanUser>::iterator	clientsIt;
		for (clientsIt = clients.begin(); clientsIt != clients.end(); clientsIt++)
		{
			if (*clientsIt->second.isOp)
				nOp++;
			std::cout << "nick = " << clientsIt->first << std::endl;
		}
		if (*cu->isOp && nOp == 1)
		{
			clientsIt = clients.begin();
			if (clientsIt->first == cu->client->nick)
				clientsIt++;
			if (clients.size() > 1)
			{
				cu = channel->getClientByNick(clientsIt->first);
				*cu->isOp = true;
			}
		}
		client->eraseChannel(*chanIt);
		channel->eraseClient(client->nick);
		channel->sendToAll(RPL_CMD(client->nick, client->user, "PART", (channel->getName() + " " + reason)));
		if (channel->getClients().size() == 0)
			server->rmChannel(channel);
	}
}
