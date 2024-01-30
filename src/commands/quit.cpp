/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:40 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/30 17:38:36 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	quitCmd(Client *client, const Command &command, Server *server)
{
	(void) command;
	client->leaveAll(server);
	server->rmClient(client);
	if (client->nick == "bot")
	{
		std::vector<pollfd>	fds = server->getFds();
		for (size_t i = 0; i < fds.size(); i++)
		{
			if (fds[i].fd == server->getBotFd())
			{
				server->eraseCloseFd(i);
				break ;
			}
		}
	}
}