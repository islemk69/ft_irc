/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:18:05 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/12 16:36:42 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	userCmd(Client *client, const Command &command, Server *server)
{
	if (!client->hasPass)
	{
		Server::sendToClient(client->fd, std::string("Error : PASS is needed to register\r\n"));
		return ;
	}
	if (command.args.empty() || command.args.size() < 3)
	{
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
		return ;
	}
	if (client->user.length() != 0)
	{
		Server::sendToClient(client->fd, ERR_ALREADYREGISTERED(client->nick));
		return ;
	}
	client->user = command.args[0];
	if (command.args.size() > 3)
	{
		client->real = command.args[3];
		if (client->real[0] == ':')
			client->real.erase(0, 1);
	}
}