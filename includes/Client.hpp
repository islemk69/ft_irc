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
        std::string nickName;
        std::string userName;
        std::string realName;
        std::string previousNickname;
        std::string socketBuffer;
        std::string awayMessage;
        int          getClientFd();
        Channel 	*getChannelByName(const std::string& name);
        
};

#endif