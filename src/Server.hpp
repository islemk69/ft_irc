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
#include <cerrno>
#include "Client.hpp"



# define PORT 6667

#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define DEFAULT "\033[0m"


# define ERR_NONICKNAMEGIVEN(nick) ("AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHh\n")

class Client;

class Server{
    private:
        unsigned int _port;
        std::string _password;
        std::vector<pollfd> _fds;
        int _serverSocket;
        std::map<int, Client*> _clients;
    public:
        Server(Server &cpy);
        Server(std::string port, std::string password);
        void initServer();
        void execServer();
        int getServerSocket();
        static void sendToClient(int fd, const std::string &content);
        ~Server();
};

#endif