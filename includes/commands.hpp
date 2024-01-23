/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charlie <charlie@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:06:52 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/22 17:24:09 by charlie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "Server.hpp"
# include "utils.hpp"

# define TARGETMAX 30
# define CHANJOINMAX 15
# define CHANNAMEMAXLEN 32

class Client;
class Server;

// ANY-USER COMMANDS
void	passCmd(Client *client, const Command &command, Server *server);
void	nickCmd(Client *client, const Command &command, Server *server);
void	userCmd(Client *client, const Command &command, Server *server);
void	joinCmd(Client *client, const Command &command, Server *server);
void	privmsgCmd(Client *client, const Command &command, Server *server);

// OPERATOR COMMANDS
void	kickCmd(Client *client, const Command &command, Server *server);
void	inviteCmd(Client *client, const Command &command, Server *server);
void	topicCmd(Client *client, const Command &command, Server *server);
void	modeCmd(Client *client, const Command &command, Server *server);

// HEXCHAT AUTOMATIC COMMANDS
void	whoCmd(Client *client, const Command &command, Server *server);

#endif
