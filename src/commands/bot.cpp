#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const char* SERVER_ADDRESS = "127.0.0.1";
const int SERVER_PORT = 6667;
const char* NICKNAME = "MyBot";
const char* USER = "myuser 0 * :My Bot";

class IRCBot {
private:
    int ircSocket;
    sockaddr_in serverAddress;
    bool connected;

public:
    IRCBot(char * pass) : connected(false) {
        ircSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ircSocket == -1) {
            std::cerr << "Error: Unable to create socket\n";
            return;
        }
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(SERVER_PORT);
        inet_pton(AF_INET, SERVER_ADDRESS, &serverAddress.sin_addr);

        if (connect(ircSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "Error: Unable to connect to IRC server\n";
            close(ircSocket);
            return;
        }

        char message1[512];
		sprintf(message1, "PASS pass\r\n");
        send(ircSocket, message1, strlen(message1), 0);

		char message2[512];
        sprintf(message2, "NICK bot %s\r\n", pass);
        send(ircSocket, message2, strlen(message2), 0);

		char message3[512];
        send(ircSocket, message3, strlen(message3), 0);

        connected = true;
    }

    bool isConnected() const {
        return connected;
    }

    void run() {
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

    ~IRCBot() {
        close(ircSocket);
    }
};

int main(int argc, char **argv) {
	if (argc != 2)
		 std::cerr << "Error: Unable to create IRC bot" << std::endl;
    IRCBot bot(argv[1]);
    if (bot.isConnected()) {
        bot.run();
    } else {
        std::cerr << "Error: Unable to create IRC bot\n";
        return 1;
    }

    return 0;
}
