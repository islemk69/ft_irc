/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:27:22 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/29 13:54:37 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Command.hpp"
#include "../includes/utils.hpp"
#include "../includes/Server.hpp"

Command::Command()
{
}

bool Command::isAllCaps(const std::string& str) {
    for (std::string::const_iterator it = str.begin(); it != str.end(); ++it) {
        if (!std::isupper(*it)) {
            return false;
        }
    }
    return true;
}

Command::Command(std::string msg) : isValid(true)
{
    if (msg.empty() || msg[0] == ' ') {
        this->isValid = false;
        return ;
    }
    std::vector<std::string> splitCmd = ft_split2(msg, " ");
    if (splitCmd.size() == 0) {
        this->isValid = false;
        return ;
    }

    this->command = splitCmd[0];
    splitCmd.erase(splitCmd.begin());
    std::string::iterator it;
    for (it = this->command.begin(); it != this->command.end(); it++) {
        if (!std::isalnum(*it)) {
            this->isValid = false;
            return ;
        }
        *it = toupper(*it);
    }

    std::vector<std::string>::iterator itVec;
    for (itVec = splitCmd.begin(); itVec != splitCmd.end(); itVec++) {
        this->args.push_back(*itVec);
    }
}

Command::~Command()
{
}

std::ostream &operator<<(std::ostream &os, const Command &c) {
    os << "Command: " << c.command << std::endl;
    os << "Args: ";
    for (size_t i = 0; i < c.args.size(); ++i) {
        os << c.args[i] << " ";
    }
    os << std::endl;
    return os;
}