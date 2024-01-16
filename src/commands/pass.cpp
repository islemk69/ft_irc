/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:09:30 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/12 16:33:29 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	passCmd(Client *client, const Command &command, Server *server)
{
	if (client->hasPass)
		return ;
	if (client->isRegistered)
		Server::sendToClient(client->fd, ERR_ALREADYREGISTERED(client->nick));
	else if (command.args.empty() || !command.args[0].length())
		Server::sendToClient(client->fd, ERR_NEEDMOREPARAMS(client->nick, command.command));
	else if (command.args.size() == 1 && command.args[0] == server->getPassword())
		client->hasPass = true;
	else{
		Server::sendToClient(client->fd, ERR_PASSWDMISMATCH(client->nick));
	}

}