#pragma once

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdio>
#include <unistd.h>
#include <csignal>

const char* SERVER_ADDRESS = "127.0.0.1";
const int SERVER_PORT = 6667;
const char* USER = "myuser 0 * :My Bot";

int ircSocket;

void handleCtrlC(int signum) {
	char message4[512];
	sprintf(message4, "QUIT :Leaving\r\n");
	send(ircSocket, message4, strlen(message4), 0);
    std::cerr << "Ctrl+C detected. Exiting...\n";
    ::_exit(0);
}

class Bot {

private:
    sockaddr_in serverAddress;
    bool connected;

public:
    Bot(char * pass) : connected(false) {
        ircSocket = socket(AF_INET, SOCK_STREAM, 0);
        if (ircSocket == -1) {
            std::cerr << "Error: Unable to create socket\n";
            return;
        }
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_port = htons(6667);
        inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);
		
        if (connect(ircSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) == -1) {
            std::cerr << "Error: Unable to connect to IRC server\n";
            close(ircSocket);
            return;
        }
		signal(SIGINT, handleCtrlC);
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

    ~Bot() {
        close(ircSocket);
    }
};