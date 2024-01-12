/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:51:23 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/09 17:39:53 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/commands.hpp"

void	kickCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty() || command.args.size() < 2)
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	Channel	*channel = server->getChannelByName(command.args[1])
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, command.args[1]));
		return ;
	}
	channel = client->getChannelByName(command.args[1])
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOTONCHANNEL(client->nick, command.args[1]));
		return ;
	}
	chanUser *cu = channel->getClientByNick(client->nick);
	if (channel->hasMode('i') && !cu->isOp)
	{
		Server::sendToClient(client->fd, ERR_CHANOPRIVSNEEDED(client->nick, channel->name));
		return ;
	}
	Client	*target = server->getClientByNick(command.args[0]);
	if (!target)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, command.args[0]));
		return ;
	}
	if (!channel->getClientByNick(target->nick))
	{
		Server::sendToClient(client->fd, ERR_USERNOTINCHANNEL(client->nick, target->nick, channel->name));
		return ;
	}
	std::string	reason = "";
	if (request.args.size() > 2)
		reason = request.args[2];
	Server::sendToClient(target->fd, RPL_CMD(target->nick, target->user, \
		"KICK", channel->name + " " + client->nick + " " + reason));
	channel->sendToAll(RPL_CMD(client->nick, client->user, \
		"KICK", channel->name + " " + target->nick + " " + reason));
	target->eraseChannel(channel->name);
	channel->eraseClient(target->nick);
}