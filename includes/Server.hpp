#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <poll.h>
#include <map>
#include <algorithm>
#include <cerrno>
#include "Client.hpp"
#include "Channel.hpp"
#include "numericReplies.hpp"



# define PORT 6667

#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define DEFAULT "\033[0m"



class Client;
class Channel;

class Server{

    private:

        unsigned int                    _port;
        int                             _serverSocket;

        std::vector<pollfd>             _fds;
        std::map<std::string, Channel*> _channels;
        std::map<int, Client*>          _clients;

        std::string 					_password;
        std::string 					_name;
        std::string 					_creationDate;

    public:

        Server(Server &cpy);
        Server(std::string port, std::string password);
        void        initServer();
        void        execServer();
        int         getServerSocket();
        void        readClientRequest(int i);
        static void sendToClient(int fd, const std::string &content);
        Client 		*getClientByNick(const std::string &nick);
        void        addChannel(Channel *newChannel);
        Channel     *getChannelByName(const std::string& name);
        std::string getPassword()const;
        ~Server();

};

#endif