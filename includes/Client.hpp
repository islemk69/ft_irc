/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:27:33 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/29 13:27:34 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"
#include "Channel.hpp"

class Channel;

class Client {

    private:

        std::map<std::string, Channel*> _channels;
        std::string                     _mode;

    public:

        Client(int fd);
        ~Client();
        bool		hasPass;
        bool        isRegistered;
        std::string nick;
        std::string user;
        std::string real;
        int         fd;//ici fd on peut retrouver le client grace a son fd
        // std::string socketBuffer;
        void         addChannel(Channel *newChannel);   
        Channel 	*getChannelByName(const std::string& name);
        void        leaveAll(Server *server);
        void        eraseChannel(const std::string & target);
        void        leaveChannel(Channel *channel, std::string cause, Server *server);
        int         chansJoined();
		std::map<std::string, Channel*> getChannels()const;
};

#endif
