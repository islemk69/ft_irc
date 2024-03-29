/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 16:52:05 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/31 18:01:34 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

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
		Server::sendToClient(client->fd, RPL_CHANNELMODEIS(client->nick, channel->getName(), channel->getModes()));
		return ;
	}
	chanUser	*cu = channel->getClientByNick(client->nick);
	if (!*cu->isOp)
	{
		Server::sendToClient(client->fd, ERR_CHANOPRIVSNEEDED(client->nick, channel->getName()));
		return ;
	}
	int							op = 0;
	int							flagsWithParams = 0;
	std::string					plusMinusO = "+o";
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
				if (!op)
					plusMinusO = "-o";
				flags.push_back(plusMinusO + " " + command.args[2 + flagsWithParams]);
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
				Server::sendToClient(client->fd, std::string(std::string("Error : MODE flag not managed : ") + command.args[1][i] + std::string("\r\n")));
				break ;
		}
	}
	
	if (flags.empty())
		return ;
		
	int	opBot = 0;
	
	for (std::vector<std::string>::iterator flagsIt = flags.begin(); flagsIt != flags.end(); flagsIt++)
	{
		std::string									flagsItStr;
		std::string									strTarget;
		Client										*target;
		// for l
		std::string									limitStr;
		std::istringstream							limitIss;
		int											limitValue;
		// for o
		std::map<std::string, chanUser>				clients;
		std::map<std::string, chanUser>::iterator	clientsIt;
		std::string									names;

		flagsItStr = *flagsIt;
		
		switch (flagsItStr[1])
		{
			case 'i' :
				flagsItStr[0] == '+' ? channel->addMode('i') : channel->rmMode('i');
				break ;
			case 't' :
				flagsItStr[0] == '+' ? channel->addMode('t') : channel->rmMode('t');
				break ;
			case 'k' :
				if (flagsItStr[0] == '+')
				{
					std::string	newKey = flagsItStr;
					newKey.erase(0, 3);
					channel->addMode('k');
					channel->setKey(newKey);
				}
				else
					channel->rmMode('k');
				break ;
			case 'o' :
				strTarget = flagsItStr;
				strTarget.erase(0, 3);
				target = server->getClientByNick(strTarget);
				if (!target)
				{
					Server::sendToClient(client->fd, ERR_NOSUCHNICK(client->nick, strTarget));
					break ;
				}
				if (strTarget == "bot")
				{
					opBot++;
					break ;
				}
				cu = channel->getClientByNick(strTarget);
				if (!cu)
				{
					Server::sendToClient(client->fd, ERR_USERNOTINCHANNEL(client->nick, strTarget, channel->getName()));
					break ;
				}
				if (flagsItStr[0] == '+')
					*cu->isOp = true;
				else
					*cu->isOp = false;
				break ;
			case 'l' :
				if (flagsItStr[0] == '+')
				{
					limitStr = flagsItStr;
					limitStr.erase(0, 3);
					limitIss.str(limitStr);
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
				return ;
		}
	}
	std::string	modeReply = "";

	for (int i = 0; i < command.args.size(); i++)
	{
		modeReply.append(command.args[i]);
		if (i < command.args.size() - 1)
			modeReply.append(" ");
	}
	channel->sendToAll(RPL_CMD(client->nick, client->user, "MODE", modeReply));
	if (opBot)
		channel->sendToAll(RPL_CMD(client->nick, client->user, "MODE", channel->getName() + " -o bot"));
}