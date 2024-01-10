/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:09:30 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/08 16:15:34 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../commands.hpp"

void	passCmd(Client *client, const Command &command, Server *server)
{
	if (client->hasPass)
		return ;
	if (client->isRegistered)
		Server::sendToClient(client->fd, ERR_ALREADYREGISTERED(client->nick));
	else if (command.args.empty() || !request.args[0].length())
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command))
	else if (command.args.size() == 1 && commmand.args[0] == server->getPassword())
		client->hasPass = true;
	else
		Server::sendToClient(client->fd, ERR_PASSWDMISMATCH(client->nick))
}