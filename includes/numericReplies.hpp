/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numericReplies.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 17:19:04 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/09 14:32:44 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NUMERICREPLIES_HPP
# define NUMERICREPLIES_HPP

# define SERVER_NAME FT_IRC

// ---- CUSTOM RPL_* ----

# define RPL_CMD(nick, user, cmd, reply) (":" + nick + "!" + user + "@localhost" + " " \
	+ cmd + " " + reply + "\r\n")

# define RPL_INVITE(nick, user, target, channel) (":" + nick + "!" + user + "@localhost" \
	+ " INVITE " + target + " " + channel + "\r\n")

# define RPL_NICK(previousNick, newNick, user) (":" + previousNick + "!" + user + "@localhost" \
	+ " NICK " + newNick + "\r\n")

# define RPL_UPDATEMODE(nick, user, channel, sign, mode, arg) (":" + nick + "!" + user + "@localhost" \
	+ " MODE " + channel + " " + sign + mode + " " + arg + "\r\n")

// ---- NUMERICS : RPL_* ----

# define RPL_AWAY(nick, target, message) (":" + SERVER_NAME + " 301 " \
	+ nick + " " + target + " :" + message + "\r\n")

# define RPL_TOPIC(nick, channel, topic) (":" + SERVER_NAME + " 302 " \
	+ nick + " " + channel + " :" + topic + "\r\n")

# define RPL_CHANNELMODEIS(nick, channel, modestring) (":" + SERVER_NAME + " 324 " \
	+ nick + " " + channel + " " + modestring + "\r\n")

# define RPL_CREATIONTIME(nick, channel, creationtime) (":" + SERVER_NAME + " 329 " \
	+ nick + " " + channel + " " + creationtime + "\r\n")

# define RPL_NOTOPIC(nick, channel) (":" + SERVER_NAME + " 331 " \
	+ nick + " " + channel + " :No topic is set\r\n")

# define RPL_TOPICWHOTIME(nick, channel, who, time) (":" + SERVER_NAME + " 333 " \
	+ nick + " " + channel + " " + who + " " + time + "\r\n")

# define RPL_INVITING(nick, target, channel) (":" + SERVER_NAME + " 341 " \
	+ nick + " " + target + " " + channel + "\r\n")

# define RPL_NAMREPLY(nick, symbol, channel, names) (":" + SERVER_NAME + " 353 " \
	+ nick + " " + symbol + " " + channel + " " + names + "\r\n")

# define RPL_ENDOFNAMES(nick, channel) (":" + SERVER_NAME + " 366 " \
	+ nick + " " + channel + " :End of /NAMES list\r\n")

// ---- NUMERICS : ERR_* ----

# define ERR_NOSUCHNICK(nick, target) (":" + SERVER_NAME + " 401 " \
	+ nick + " " + target + " :No such nick/channel\r\n")

# define ERR_NOSUCHCHANNEL(nick, channel) (":" + SERVER_NAME + " 403 " \
	+ nick + " " + channel + " :No such channel\r\n")

# define ERR_CANNOTSENDTOCHAN(nick, channel) (":" + SERVER_NAME + " 404 " \
	+ nick + " " + channel + " :Cannot send to channel\r\n")

# define ERR_TOOMANYCHANNELS(nick, channel) (":" + SERVER_NAME + " 405 " \
	+ nick + " " + channel + " :You have joined too many channels\r\n")

# define ERR_TOOMANYTARGETS(nick) ((":" + SERVER_NAME + " 407 " \
	+ nick + " :Too many targets for private message\r\n"))

# define ERR_NORECIPIENT(nick, command) (":" + SERVER_NAME + " 411 " \
	+ nick + " :No recipient given (<" + command + ">)\r\n")

# define ERR_NOTEXTTOSEND(nick) ((":" + SERVER_NAME + " 412 " \
	+ nick + " :No text to send\r\n"))

# define ERR_UNKNOWNCOMMAND(nick, command) ((":" + SERVER_NAME + " 421 " \
	+ nick + " " + command + " :Unknown command\r\n"))

# define ERR_NONICKNAMEGIVEN(nick) (":" + SERVER_NAME + " 431 " \
	+ nick + " :No nickname given\r\n")

# define ERR_ERRONEUSNICKNAME(nick) (":" + SERVER_NAME + " 432 " \
	+ nick + " :Erroneus nickname\r\n")

# define ERR_NICKNAMEINUSE(nick) (":" + SERVER_NAME + " 433 " \
	+ nick + " :Nickname is already in use\r\n")

# define ERR_USERNOTINCHANNEL(nick, target, channel) (":" + SERVER_NAME + " 441 " \
	+ nick + " " + target + " " + channel + " :They aren't on that channel\r\n")

# define ERR_NOTONCHANNEL(nick, channel) (":" + SERVER_NAME + " 442 " \
	+ nick + " " + channel + " :You're not on that channel\r\n")

# define ERR_USERONCHANNEL(nick, target, channel) (":" + SERVER_NAME + " 443 " \
	+ nick + " " + target + " " + channel + " :is already on channel\r\n")

# define ERR_NEEDMOREPARAMS(nick, command) (":" + SERVER_NAME + " 461 " \
	+ nick + " " + command + " :Not enough parameters\r\n")

# define ERR_ALREADYREGISTERED(nick) (":" + SERVER_NAME + " 462 " \
	+ nick + " :You may not reregister\r\n")

# define ERR_PASSWDMISMATCH(nick) (":" + SERVER_NAME + " 464 " \
	+ nick + " :Password incorrect\r\n")

# define ERR_CHANNELISFULL(nick, channel) (":" + SERVER_NAME + " 471 " \
	+ nick + " :Cannot join channel (+l)\r\n")

# define ERR_INVITEONLYCHAN(nick, channel) (":" + SERVER_NAME + " 473 " \
	+ nick + " " + channel + " :Cannot join channel (+i)\r\n")

# define ERR_BADCHANNELKEY(nick, channel) (":" + SERVER_NAME + " 475 " \
	+ nick + " " + channel + " :Cannot join channel (+k)\r\n")

# define ERR_BADCHANMASK(channel) (":" + SERVER_NAME + " 476 " \
	+ channel + " :Bad Channel Mask\r\n")

# define ERR_CHANOPRIVSNEEDED(nick, channel) (":" + SERVER_NAME + " 482 " \
	+ nick + " " + channel + " :You're not channel operator\r\n")

# define ERR_INVALIDKEY(nick, channel) (":" + SERVER_NAME + " 525 " \
	+ nick + " " + channel + " :Key is not well-formed\r\n")

#endif