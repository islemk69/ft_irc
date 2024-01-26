/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 13:58:23 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/23 18:39:46 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	inviteCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty() || command.args.size() < 2)
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	Channel	*channel = server->getChannelByName(command.args[1]);
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, command.args[1]));
		return ;
	}
	channel = client->getChannelByName(command.args[1]);
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOTONCHANNEL(client->nick, command.args[1]));
		return ;
	}
	chanUser *cu = channel->getClientByNick(client->nick);
	if (channel->hasMode('i') && !*cu->isOp)
	{
		Server::sendToClient(client->fd, ERR_CHANOPRIVSNEEDED(client->nick, channel->getName()));
		return ;
	}
	Client	*target = server->getClientByNick(command.args[0]);
	if (!target)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, command.args[0]));
		return ;
	}
	if (channel->getClientByNick(target->nick))
	{
		Server::sendToClient(client->fd, ERR_USERONCHANNEL(client->nick, target->nick, channel->getName()));
		return ;
	}
	Server::sendToClient(client->fd, RPL_INVITING(client->nick, target->nick, channel->getName()));
	Server::sendToClient(target->fd, RPL_INVITE(client->nick, client->user, target->nick, channel->getName()));
	channel->addInvite(target->nick);
}