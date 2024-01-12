/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:05 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/12 16:47:19 by ikaismou         ###   ########.fr       */
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
	if (channel->hasMode('t') && !cu->isOp)
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
	std::string	newTopic = command.args[1];
	if (newTopic[0] == ':')
		newTopic.erase(0, 1);
	channel->setTopic(newTopic);
	channel->sendToAll(RPL_CMD(client->nick, client->user, "TOPIC", channel->getName() + " :" + channel->getTopic()));
}