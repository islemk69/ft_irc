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
#include <sstream>
#include "Command.hpp"
#include "commands.hpp"
#include "Client.hpp"
#include "Channel.hpp"
#include "numericReplies.hpp"
#include "utils.hpp"



# define PORT 6667

#define YELLOW "\033[1;33m"
#define GREEN "\033[1;32m"
#define RED "\033[1;31m"
#define DEFAULT "\033[0m"



class Client;
class Channel;

class Server{


    public:

        Server(Server &cpy);
        Server(std::string port, std::string password);
        void        initServer();
        void        initCommand();
        void        execServer();
        int         getServerSocket();
        void        readClientRequest(int i);
        static void sendToClient(int fd, const std::string &content);
        Client 		*getClientByNick(const std::string &nick);
        Client      *getClientFromFd(int fd);
        void        addChannel(Channel *newChannel);
        Channel     *getChannelByName(const std::string& name);
        std::string getPassword()const;
		void		updateClient(std::string oldNick, std::string newNick);	
		bool		isNickUsed(Client *client, std::string nick);

        bool        buffContainsEndOfMsg(std::string & msgBuffer) const;


        ~Server();

        //typedef pour fonction de command qui prend en arguments le client une ref constante sur la commande et un pointeru sur le serveur
        typedef void (*cmdFct) (Client *client, const Command &cmd, Server *server);
        //un iterator qui peret de passer 
        typedef std::map<std::string, cmdFct>::iterator CmdIt;

    private:

        unsigned int                    _port;
        int                             _serverSocket;

        std::vector<pollfd>             _fds;
        std::map<std::string, Channel*> _channels;
        std::map<int, Client*>          _clients;
        std::map<std::string, cmdFct>   _cmds;
        std::string 					_password;
        std::string 					_name;
        std::string 					_creationDate;
};

#endif
