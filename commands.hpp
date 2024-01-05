/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:06:52 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/05 17:18:06 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMANDS_HPP
# define COMMANDS_HPP

# include "src/server.hpp"

// ANY-USER COMMANDS
void	passCmd();
void	nickCmd();
void	userCmd();
void	joinCmd();
void	privmsgCmd();

// OPERATOR COMMANDS
void	kickCmd();
void	inviteCmd();
void	topicCmd();
void	modeCmd();

#endif