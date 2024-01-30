#include "../includes/Bot.hpp"

Bot::Bot(char *port, char *pass, char *passBot) : connected(false) {
	ircSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ircSocket == -1) {
            std::cerr << "Error: Unable to create socket\n";
            return;
        }
        serverAddress.sin_family = AF_INET;

		std::istringstream iss(port);
		int portNumber;
		iss >> portNumber;
		if (iss.fail() || portNumber < 1 || portNumber > 65535){
			std::cerr << "Error wrong port number" << std::endl;
			::_exit(1);
		}
        serverAddress.sin_port = htons(portNumber);
        inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
		
        if (connect(ircSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "Error: Unable to connect to IRC server\n";
            close(ircSocket);
            return;
        }
		signal(SIGINT, handleCtrlC);
        char message1[512];
		sprintf(message1, "PASS %s\r\n", pass);
        send(ircSocket, message1, strlen(message1), 0);

		char message2[512];
        sprintf(message2, "NICK bot %s\r\n", passBot);
        send(ircSocket, message2, strlen(message2), 0);

		char message3[512];
		// sprintf(message2, "NICK bot %s\r\n", passBot);"myuser 0 * :My Bot"
        send(ircSocket, message3, strlen(message3), 0);
        connected = true;
}


bool Bot::isConnected() const {
	return connected;
}


void Bot::run() {
	char buffer[1024];
	while (true) {
		int bytesReceived = recv(ircSocket, buffer, sizeof(buffer), 0);
		if (bytesReceived == -1) {
			std::cerr << "Error receiving data from server\n";
			break;
		} else if (bytesReceived == 0) {
			std::cerr << "Server closed connection\n";
			break;
		} else {
			buffer[bytesReceived] = '\0';
			std::cout << "Received: " << buffer;
			
		}
	}
}

Bot::~Bot() {
	close(ircSocket);
}

int main(int argc, char **argv) {
	if (argc != 4){
		 std::cerr << "./bot <port> <pass> <key>" << std::endl;
		 return 1;
	}
    Bot bot(argv[1], argv[2], argv[3]);
    if (bot.isConnected()) {
        bot.run();
    } else {
        std::cerr << "Error: Unable to create IRC bot\n";
        return 1;
    }
    return 0;
}