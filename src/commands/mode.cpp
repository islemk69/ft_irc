/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:05 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/10 19:01:15 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../commands.hpp"

void	modeCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty() || (command.args.size() > 1 && \
		command.args[1][0] != '+' && command.args[1][0] != '-'))
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	Channel	*channel = server->getChannelByName(command.args[0]);
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, command.args[0]))
		return ;
	}
	channel = client->getChannelByName(command.args[0])
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOTONCHANNEL(client->nick, command.args[0]));
		return ;
	}
	if (command.args.size() == 1)
	{
		Server::sendToClient(client->fd, RPL_CHANNELMODEIS(client->nick, channel->name, channel->getModes()));
		Server::sendToClient(client->fd, RPL_CREATIONTIME(client->nick, channel->name, channel->getCreationTime()));
		return ;
	}
	chanUser	*cu = channel->getClientByNick(client->nick);
	if (!cu->isOp)
	{
		Server::sendToClient(client->fd, ERR_CHANOPRIVSNEEDED(client->nick, channel->name));
		return ;
	}
	// - set a map<string, string>, first string being key (ex +o / -l /...), 
	// second string being potential parameter for the cmd.
	// - exec all cmd depending on map.
	
}