/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:23:58 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/12 15:08:24 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"

class Server;
class Client;

typedef struct t_chanUser
{
    Client	*client;
    bool	isOp;
}	chanUser;

class Channel {

    private:
		int									_clientLimit;
        std::string							_name;
        std::string							_modes;
		std::string							_topic;
		std::string							_key;
		std::vector<std::string>			_invited;
		std::map<std::string, chanUser>		_chanUsers;
        Channel();

    public:

        Channel(std::string name, Client *client);
        ~Channel();
        std::string		getName() const;
		std::string		getModes() const;
		int				getNumberOfClients() const;
		int				getClientLimit() const;
        bool			hasMode(const char mode) const;
		bool			isInvited(const std::string &client) const;
        void			sendToAll(const std::string &msg);
        void			sendToAllButClient(int fd, const std::string &msg);
		void			addClient(const Client *client);
		void			addInvite(const std::string &client);
        void			eraseClient(const std::string &client);
		void			addMode(const char mode);
		void			rmMode(const char mode);
		void			setKey(const std::string &key);
		void			setClientLimit(int limit);
        chanUser		*getClientByNick(const std::string &nick);
};
#endif