/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 16:45:39 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/09 17:28:39 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/commands.hpp"

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
		Server::sendToClient(client->fd, ERR_NOSUCHCHANNEL(client->nick, commands.args[0]));
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
		std::string	topic = channel->topic;
		
		if (topic.empty())
			Server::sendToClient(client->fd, RPL_NOTOPIC(client->nick, channel->name));
		else
			Server::sendToClient(client->fd, RPL_TOPIC(client->nick, channel->name, topic));
		return ;
	}
	chanUser *cu = channel->getClientByNick(client->nick);
	if (channel->hasMode('t') && !cu->isOp)
	{
		Server::sendToClient(client->fd, ERR_CHANOPRIVSNEEDED(client->nick, channel->name))
		return ;
	}
	if (command.args[1] == ":")
	{
		channel->topic.clear();
		channel->sendToAll(RPL_CMD(client->nick, client->user, "TOPIC", channel->name + " :"));
		return ;
	}
	channel->topic = command.args[1];
	if (channel->topic[0] == ':')
		channel->topic.erase(0, 1);
	channel->sendToAll(RPL_CMD(client->nick, client->user, "TOPIC", channel->name + " :" + channel->topic));
}