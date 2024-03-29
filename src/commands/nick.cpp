/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:16:20 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/30 14:35:38 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

bool	isNickValid(std::string nick)
{
	std::string	forbiddenAll = " .,*?!@";
	std::string	forbiddenFirst = "$:#&~%+";
	if (nick.find_first_of(forbiddenAll) != std::string::npos)
		return false;
	if (forbiddenFirst.find(nick[0]) != std::string::npos)
		return false;
	return true;
}

void	nickCmd(Client *client, const Command &command, Server *server)
{
	if (!client->hasPass)
	{
		Server::sendToClient(client->fd, std::string("Error : PASS is needed to register\r\n"));
		return ;
	}
	if (command.args.empty() || command.args[0].length() == 0)
	{
		Server::sendToClient(client->fd, ERR_NONICKNAMEGIVEN(std::string("Client")));
		return ;
	}
	if ((command.args.size() > 0 && !isNickValid(command.args[0])) || \
		(command.args.size() > 1 && command.args[0] == "bot" && command.args[1] != server->getPassBot()))
	{
		Server::sendToClient(client->fd, ERR_ERRONEUSNICKNAME(command.args[0]));
		return ;
	}
	if (command.args.size() > 1 && command.args[0] == "bot" && command.args[1] != server->getPassBot())
	{
		Server::sendToClient(client->fd, std::string("Error : Bot connection refused\r\n"));
		return ;
	}
	if (server->isNickUsed(client, command.args[0]))
	{
		client->previousNick = client->previousNick.empty() ? command.args[0] : client->previousNick;
		Server::sendToClient(client->fd, ERR_NICKNAMEINUSE(command.args[0]));
		return ;
	}
	if (!client->isRegistered)
	{
		client->isRegistered = true;
		client->nick = command.args[0];

		std::string	userName = client->user.empty() ? "" : client->user;
		std::string	nickToUse = client->previousNick.empty() ? client->nick : client->previousNick;
		Server::sendToClient(client->fd, RPL_CMD(nickToUse, userName, "NICK", client->nick));
		if (client->nick == "bot")
		{
			server->setBotFd(client->fd);

			std::map<std::string, Channel*>				serverChans = server->getChannels();
			std::map<std::string, Channel*>::iterator	serverChanIt;

			for (serverChanIt = serverChans.begin(); serverChanIt != serverChans.end(); serverChanIt++)
			{
				Channel	*toJoin = serverChanIt->second;
				std::string	joinCmdStr = "JOIN " + serverChanIt->first;
				if (toJoin->hasMode('k'))
					joinCmdStr += " " + toJoin->getKey();
				Command		jCmd(joinCmdStr);
				joinCmd(client, jCmd, server);
			}
		}
	}
	else
	{
		Server::sendToClient(client->fd, RPL_CMD(client->nick, client->user, "NICK", command.args[0]));
		std::map<std::string, Channel* >	clientChans = client->getChannels();
		for (std::map<std::string, Channel* >::iterator clientChanIt = clientChans.begin(); \
			clientChanIt != clientChans.end(); clientChanIt++)
		{
			clientChanIt->second->updateClient(client->nick, command.args[0]);
			std::map<std::string, chanUser>	channelClients = clientChanIt->second->getClients();
			for (std::map<std::string, chanUser>::iterator clientIt = channelClients.begin(); \
				clientIt != channelClients.end(); clientIt++)
			{
				if (clientIt->second.client->nick != client->nick)
					Server::sendToClient(clientIt->second.client->fd, \
						RPL_CMD(client->nick, client->user, "NICK", command.args[0]));
			}
		}
		client->nick = command.args[0];
	}
}