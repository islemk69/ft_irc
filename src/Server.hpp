#ifndef SERVER_HPP
# define SERVER_HPP

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <poll.h>
#include "Client.hpp"

# define PORT 6667

#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define DEFAULT "\033[0m"

class Server{
    private:
        unsigned int _port;
        std::string _password;
        std::vector<pollfd> _fds;
        int _serverSocket;
    public:
        Server(Server &cpy);
        Server(std::string port, std::string password);
        int initServer();
        int launchServer();
        int getServerSocket();
        ~Server();
};

#endif