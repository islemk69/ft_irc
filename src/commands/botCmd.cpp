#include "../../includes/commands.hpp"

std::string getCurrentDateTime() {
    std::time_t now = std::time(0);
    std::tm* tm = std::localtime(&now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);

    return std::string(buffer);
}

void botCmd(Client* client, const Command& command, Server* server) {
	if (server->getBotFd() < 0){
		Server::sendToClient(client->fd, "No bot connected, please retry later\r\n");
		return ;
	}
		
	if (!client->isRegistered){
		Server::sendToClient(client->fd, "Please register\r\n");
		return ;
	}
		
	std::cout << "BOT DETECTE" << std::endl;
    if (command.args.size() == 0)
        Server::sendToClient(client->fd, "Please enter a bot command\r\n");
    const char* dateKeywords[] = {
        "time", "clock", "hour", "minute", "second", "calendar",
        "month", "week", "year", "century", "decade",
        "schedule", "timeline", "duration", "event", "timestamp",
        "anniversary", "deadline", "period", "epoch", "era",
        0 
    };
    const char* helloKeywords[] = {
        "hello", "hi", "hey", "greetings", "good", "morning",
        "afternoon", "day", "howdy", "yo", "there",
        "up", "how", "are", "you", "greet", "salutations", "hail",
        "aloha",
        0 
    };
	
    for (std::vector<std::string>::const_iterator it = command.args.begin(); it != command.args.end(); ++it) {
        const std::string& arg = *it;
        for (int i = 0; dateKeywords[i]; i++) {
            std::string myString(dateKeywords[i]);
            if (myString == arg) {
                std::string dateTime = getCurrentDateTime();
                Server::sendToClient(client->fd, RPL_CMD(std::string("bot"), std::string("bot"), \
				"PRIVMSG", ": " + dateTime));
                break; 
            }
        }
		for (int i = 0; helloKeywords[i]; i++) {
            std::string myString2(helloKeywords[i]);
            if (myString2 == arg) {
                Server::sendToClient(client->fd, RPL_CMD(std::string("bot"), std::string("bot"), \
				"PRIVMSG", ": " + "Hellooo \U0001F600"));
                break; 
            }
        }
    }
}