/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:23:58 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/12 16:49:18 by ikaismou         ###   ########.fr       */
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
        std::string						getName() const;
		std::string						getModes() const;
		std::string						getKey() const;
		std::string						getTopic() const;
		int								getNumberOfClients() const;
		int								getClientLimit() const;
        bool							hasMode(const char mode) const;
		bool							isInvited(const std::string &client) const;
        void							sendToAll(const std::string &msg);
        void							sendToAllButClient(int fd, const std::string &msg);
		void							addInvite(const std::string &client);
		void							addClient(Client *client);
        void							eraseClient(const std::string &client);
		void							addMode(const char mode);
		void							rmMode(const char mode);
		void							setKey(const std::string &key);
		void							setTopic(const std::string &newTopic);
		void							setClientLimit(int limit);
		void							updateClient(std::string oldNick, std::string newNick);
        chanUser						*getClientByNick(const std::string &nick);
		std::map<std::string, chanUser>	getClients() const;
};
#endif