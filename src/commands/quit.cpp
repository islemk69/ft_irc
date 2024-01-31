/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:40 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/31 13:46:02 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	quitCmd(Client *client, const Command &command, Server *server)
{
	(void) command;
	client->leaveAll(server);
	std::vector<pollfd>	fds = server->getFds();
	for (size_t i = 0; i < fds.size(); i++)
	{
		if (fds[i].fd == client->fd)
		{
			server->eraseCloseFd(i);
			break ;
		}
	}
	server->rmClient(client);
}