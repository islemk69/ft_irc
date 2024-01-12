/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 17:29:46 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/12 16:35:50 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	privmsgCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty())
	{
		Server::sendToClient(client->fd, ERR_NORECIPIENT(client->nick, command.command));
		return ;
	}
	std::vector<std::string>	targets = ft_split(command.args[0], ',');

	if (targets.size() > TARGETMAX)
	{
		Server::sendToClient(client->fd, ERR_TOOMANYTARGETS(client->nick));
		return ;
	}
	for(std::vector<std::string>::iterator it = targets.begin(); it != targets.end(); it++)
	{
		if (it->find("#") == 0)
		{
			std::string	chanName = *it;
			chanName.erase(0, 1);
			Channel		*channel = server->getChannelByName(chanName);
			if (!channel)
			{
				Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, chanName));
				continue ;
			}
			channel = client->getChannelByName(chanName);
			if (!channel)
			{
				Server::sendToClient(client->fd, ERR_CANNOTSENDTOCHAN(client->nick, chanName));
				continue ;
			}
			if (command.args.size() < 2 || command.args[1].empty())
			{
				Server::sendToClient(client->fd, ERR_NOTEXTTOSEND(client->nick));
				return ;
			}
			channel->sendToAllButClient(client->fd, RPL_CMD(client->nick, client->user, \
				"PRIVMSG " + chanName, command.args[1]));
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
			Server::sendToClient(target->fd, RPL_CMD(client->nick, client->user, \
				"PRIVMSG", ": " + command.args[1]));
		}
	}
}