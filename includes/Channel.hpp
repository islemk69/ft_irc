#ifndef CHANNEL_HPP
# define CHANNEL_HPP

#include "Client.hpp"


class Server;
class Client;

class Channel {
public:
	Channel(std::string name);
	Channel();
    ~Channel();
    std::string     getName() const;

private:
    std::string _name;  
};
#endif