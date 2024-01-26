/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 16:57:40 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/26 15:36:29 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"

void	quitCmd(Client *client, const Command &command, Server *server)
{
	(void) command;

	client->leaveAll(server);
	server->rmClient(client);
}