#ifndef BOT_HPP
# define BOT_HPP


#include "Server.hpp"


int ircSocket;

void handleCtrlC(int signum) {
	char message4[512];
	sprintf(message4, "QUIT :Leaving\r\n");
	send(ircSocket, message4, strlen(message4), 0);
    ::_exit(0);
}

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