/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:29:46 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/26 15:05:27 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"
#include "../../includes/utils.hpp"

void	privmsgCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty())
	{
		Server::sendToClient(client->fd, ERR_NORECIPIENT(client->nick, command.command));
		return ;
	}
	std::vector<std::string>	targets = ft_split(command.args[0], ",");

	if (targets.size() > TARGETMAX)
	{
		Server::sendToClient(client->fd, ERR_TOOMANYTARGETS(client->nick));
		return ;
	}
	for(std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); it++)
	{
		if (it->find("#") == 0)
		{
			Channel		*channel = server->getChannelByName(*it);
			if (!channel)
			{
				Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, *it));
				continue ;
			}
			channel = client->getChannelByName(*it);
			if (!channel)
			{
				Server::sendToClient(client->fd, ERR_CANNOTSENDTOCHAN(client->nick, *it));
				continue ;
			}
			if (command.args.size() < 2 || command.args[1].empty())
			{
				Server::sendToClient(client->fd, ERR_NOTEXTTOSEND(client->nick));
				return ;
			}

			std::string completeMsg = joinStr(command.args);
			
			channel->sendToAllButClient(client->fd, RPL_CMD(client->nick, client->user, \
				"PRIVMSG " + *it, completeMsg));
		}
		else
		{
			std::string targetName = *it;
			Client		*target = server->getClientByNick(targetName);
			if (!target)
			{
				Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, targetName));
				continue ;
			}
			if (command.args.size() < 2 || command.args[1].empty())
			{
				Server::sendToClient(client->fd, ERR_NOTEXTTOSEND(client->nick));
				return ;
			}

			std::string completeMsg = joinStr(command.args);

			std::cout << "complete msg = " << completeMsg << "sent to = " << target->nick << std::endl;
			Server::sendToClient(target->fd, RPL_CMD(client->nick, client->user, \
				"PRIVMSG", ": " + completeMsg));
		}
	}
}