/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:06:52 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/08 15:13:20 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "src/server.hpp"
# include "numericReplies.hpp"

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

#endif