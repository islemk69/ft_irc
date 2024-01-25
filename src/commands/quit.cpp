/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:40 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/25 15:18:28 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	quitCmd(Client *client, const Command &command, Server *server)
{
	(void) command;

	client->leaveAll(server);
	Server::sendToClient(client->fd, std::string("Error: Disconnected\r\n"));
	server->rmClient(client);
}