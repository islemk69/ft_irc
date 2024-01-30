#ifndef BOT_HPP
# define BOT_HPP


#include "Server.hpp"

class Bot {

private:
    sockaddr_in serverAddress;
    bool connected;
	std::vector<std::string> command;

public:
	Bot(char *port, char *pass, char *passBot);
	bool isConnected() const;
	void run();
	~Bot();
};

#endif