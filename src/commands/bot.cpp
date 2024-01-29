/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:27:55 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/29 13:27:56 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/commands.hpp"
#include <vector>
#include <string>
#include <ctime>

std::string getCurrentDateTime() {
    std::time_t now = std::time(0);
    std::tm* tm = std::localtime(&now);

    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm);

    return std::string(buffer);
}

void botCmd(Client* client, const Command& command, Server* server) {
    if (command.args.size() == 0)
        Server::sendToClient(client->fd, "Veuillez rentrer une commande bot\r\n");

    const char* dateKeywords[] = {
        "time", "clock", "hour", "minute", "second", "calendar",
        "month", "week", "year", "century", "decade",
        "schedule", "timeline", "duration", "event", "timestamp",
        "anniversary", "deadline", "period", "epoch", "era",
        0  // Marqueur de fin du tableau
    };

    const char* helloKeywords[] = {
        "hello", "hi", "hey", "greetings", "good", "morning",
        "afternoon", "day", "howdy", "yo", "there",
        "up", "how", "are", "you", "greet", "salutations", "hail",
        "aloha",
        0  // Marqueur de fin du tableau
    };

    for (std::vector<std::string>::const_iterator it = command.args.begin(); it != command.args.end(); ++it) {
        const std::string& arg = *it;
        for (int i = 0; dateKeywords[i]; i++) {
            std::string myString(dateKeywords[i]);
            // Comparer les chaînes (insensible à la casse)
            if (myString == arg) {
                std::string dateTime = getCurrentDateTime();
                Server::sendToClient(client->fd, dateTime + "\r\n");
                return ;  // Sortir de la boucle dès qu'une correspondance est trouvée
            }
        }
		for (int i = 0; helloKeywords[i]; i++) {
            std::string myString(helloKeywords[i]);
            // Comparer les chaînes (insensible à la casse)
            if (myString == arg) {
                Server::sendToClient(client->fd, "Hellooooow \U0001F604\U0001F604\r\n");
                return ;  // Sortir de la boucle dès qu'une correspondance est trouvée
            }
        }
    }
}