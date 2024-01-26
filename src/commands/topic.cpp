/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:05 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/26 16:33:19 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	topicCmd(Client *client, const Command &command, Server *server)
{
	if (command.args.empty())
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	Channel	*channel = server->getChannelByName(command.args[0]);
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, command.args[0]));
		return ;
	}
	channel = client->getChannelByName(command.args[0]);
	if (!channel)
	{
		Server::sendToClient(client->fd, ERR_NOTONCHANNEL(client->nick, command.args[0]));
		return ;
	}
	if (command.args.size() == 1)
	{
		std::string	topic = channel->getTopic();

		if (topic.empty())
			Server::sendToClient(client->fd, RPL_NOTOPIC(client->nick, channel->getName()));
		else
			Server::sendToClient(client->fd, RPL_TOPIC(client->nick, channel->getName(), topic));
		return ;
	}
	chanUser *cu = channel->getClientByNick(client->nick);
	if (channel->hasMode('t') && !*cu->isOp)
	{
		Server::sendToClient(client->fd, ERR_CHANOPRIVSNEEDED(client->nick, channel->getName()));
		return ;
	}
	if (command.args[1] == ":")
	{
		channel->setTopic("");
		channel->sendToAll(RPL_CMD(client->nick, client->user, "TOPIC", channel->getName() + " :"));
		return ;
	}
	std::string completeTopic = joinStr(command.args);
	if (completeTopic[0] == ':')
		completeTopic.erase(0, 1);
	channel->setTopic(completeTopic);
	channel->sendToAll(RPL_CMD(client->nick, client->user, "TOPIC", channel->getName() + " :" + channel->getTopic()));
}