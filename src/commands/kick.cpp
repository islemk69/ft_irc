/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:51:23 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/29 15:33:00 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	kickCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty() || command.args.size() < 2)
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	Channel	*channel = server->getChannelByName(command.args[0]);
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, command.args[1]));
		return ;
	}
	channel = client->getChannelByName(command.args[0]);
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOTONCHANNEL(client->nick, command.args[1]));
		return ;
	}
	chanUser *cu = channel->getClientByNick(client->nick);
	if (cu && !*cu->isOp)
	{
		Server::sendToClient(client->fd, ERR_CHANOPRIVSNEEDED(client->nick, channel->getName()));
		return ;
	}
	if (command.args[1] == "bot")
		return ;
	Client	*target = server->getClientByNick(command.args[1]);
	if (!target)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, command.args[1]));
		return ;
	}
	if (!channel->getClientByNick(target->nick))
	{
		Server::sendToClient(client->fd, ERR_USERNOTINCHANNEL(client->nick, target->nick, channel->getName()));
		return ;
	}
	std::string	reason = "";
	if (command.args.size() > 2)
		reason = command.args[2];
	Server::sendToClient(target->fd, RPL_CMD(target->nick, target->user, \
		"KICK", channel->getName() + " " + client->nick + " " + reason));
	channel->sendToAll(RPL_CMD(client->nick, client->user, \
		"KICK", channel->getName() + " " + target->nick + " " + reason));
	target->eraseChannel(channel->getName());
	channel->eraseClient(target->nick);
}