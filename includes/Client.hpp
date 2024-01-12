#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"
#include "Channel.hpp"

class Channel;

class Client {

    private:

        int                             _clientFd;
        std::map<std::string, Channel*> _channels;
        std::string                     _mode;

    public:

        Client(int clientFd);
        ~Client();
        bool		hasPass;
        bool        isRegistered;
        std::string nick;
        std::string user;
        std::string real;
        // std::string socketBuffer;
        int          getClientFd();
        void         addChannel(Channel *newChannel);   
        Channel 	*getChannelByName(const std::string& name);
        void        leaveAll();
        void        eraseChannel(const std::string & target);
        void        leaveChannel(Channel *channel, std::string cause);
        int         chansJoined();
};

#endif