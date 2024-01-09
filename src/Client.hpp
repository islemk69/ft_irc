#ifndef CLIENT_HPP
# define CLIENT_HPP

#include "Server.hpp"

class Client {
    private:
        int         _clientFd;
    public:
        Client(int clientFd);
        ~Client();
        bool		hasPassword;
        std::string nickName;
        std::string userName;
        std::string realName;
        std::string previousNickname;
        std::string socketBuffer;
        std::string awayMessage;
        int getClientFd();
};

#endif