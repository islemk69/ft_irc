/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:05 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/12 13:09:10 by ccrottie         ###   ########.fr       */
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
	int							op = 0;
	int							flagsWithParams = 0;
	std::vector<std::string>	flags;
	
	for (size_t i = 0; i < command.args[1].length(); i++)
	{
		switch (command.args[1][i])
		{
			case '+' :
				op = 1;
				break ;
			case '-' :
				op = 0;
				break ;
			case 'i' :
				op ? flags.push_back("+i") : flags.push_back("-i");
				break ;
			case 't' :
				op ? flags.push_back("+t") : flags.push_back("-t");
				break ;
			case 'k' :
				if (op)
				{
					if (command.args.size() < 2 + flagsWithParams)
					{
						Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
						return ;
					}
					flags.push_back("+k " + command.args[2 + flagsWithParams]);
					flagsWithParams++;
				}
				else
					flags.push_back("-k");
				break ;
			case 'o' :
				if (command.args.size() < 2 + flagsWithParams)
				{
					Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
					return ;
				}
				std::string	opO = op ? "+o" : "-o";
				flags.push_back(opO + " " + command.args[2 + flagsWithParams]);
				flagsWithParams++;
				break ;
			case 'l' :
				if (op)
				{
					if (command.args.size() < 2 + flagsWithParams)
					{
						Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
						return ;
					}
					flags.push_back("+l " + command.args[2 + flagsWithParams]);
					flagsWithParams++;
				}
				else
					flags.push_back("-l");
				break ;
			default :
				Server::sendToClient(client->fd, std::string("Error : MODE flag not managed : " + command.args[1][i] + "\r\n"));
				break ;
		}
	}
	if (flags.empty())
		return ;
	for (std::vector<std::string>::iterator flagsIt = flags.begin(); flagsIt != flags.end(); flags++)
	{
		switch (*flagsIt[1])
		{
			case 'i' :
				*flagsIt[0] == '+' ? channel->addMode('i') : channel->rmMode('i');
				break ;
			case 't' :
				*flagsIt[0] == '+' ? channel->addMode('t') : channel->rmMode('t');
			case 'k' :
				if (*flagsIt[0] == '+')
				{
					std::string	newKey = *flagsIt;
					newKey.erase(0, 3);
					channel->addMode('k');
					channel->setKey(newKey);
				}
				else
				{
					channel->rmMode('k');
					channel->rmKey();
				}
				break ;
			case 'o' :
				std::string	strTarget = *flagsIt;
				strTarget.erase(0, 3);
				Client	*target = server->getClientByNick(strTarget);
				if (!target)
				{
					Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, strTarget));
					break ;
				}
				chanUser	*cu = channel->getClientByNick(strTarget);
				if (!cu)
				{
					Server::sendToClient(client->fd, ERR_USERNOTINCHANNEL(client->nick, strTarget, channel->name));
					break ;
				}
				if (*flagsIt[0] == '+')
					cu->isOp = true;
				else
					cu->isOp = false;
				break ;
			case 'l' :
				if (*flagsIt[0] == '+')
				{
					std::string	limitStr = *flagsIt;
					limitStr.erase(0, 3);
					std::istringstream	limitIss(limitStr);
					int					limitValue;
					limitIss >> limitValue;
					if (limitIss.fail() || !limitIss.eof() || limitValue <= 0 || limitValue > 4096)
					{
						Server::sendToClient(client->fd, std::string("Error : MODE +l [1-4096]"));
						return ;
					}
					channel->addMode('l');
					channel->setClientLimit(limitValue);
				}
				else
					channel->rmMode('l');
				break ;
			default :
				break ;
		}
	}	
}