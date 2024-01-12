#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"


class Server;
class Client;

class Channel {

private:

    std::string _name;  
    Server *_server;

public:

	Channel(std::string name, Client *client, Server *server);
	Channel();
    ~Channel();
    std::string     getName() const;
    void            sendToAll(const std::string &msg);
    void            eraseClient(const std::string & client);
    Client          *getClientByNick(const std::string &nick);
};
#endif