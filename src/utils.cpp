/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:37:11 by ikaismou          #+#    #+#             */
/*   Updated: 2024/01/26 15:05:00 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

std::vector<std::string> ft_split(const std::string &msg, const std::string &delim)
{
    std::vector<std::string> res;
    std::string token = "";
    for (int i = 0; i < msg.size(); i++)
    {
        bool flag = true;
        for (int j = 0; j < delim.size(); j++)
        {
            if (msg[i + j] != delim[j])
                flag = false;
        }
        if (flag)
        {
            if (token.size() > 0)
            {
                res.push_back(token);
                token = "";
                i += delim.size() - 1;
            }
        }
        else if (msg[i] == '\n') // Ajout de la vérification pour '\n'
        {
            if (token.size() > 0)
            {
                res.push_back(token);
                token = "";
            }
        }
		else if (msg[i] == '\r') // Ajout de la vérification pour '\r'
        {
            if (token.size() > 0)
            {
                res.push_back(token);
                token = "";
            }
        }
        else
        {
            token += msg[i];
        }
    }
    if (token.size() > 0)
    {
        res.push_back(token);
    }
    return res;
}


std::string copyToUpper(std::string src){
    std::string res = src;
	std::transform(src.begin(), src.end(), src.begin(), toupper);
	return res;
}

std::string joinStr(std::vector<std::string> args) {
	std::string finalString;
	for (int i = 1; i < args.size(); i++) {
		finalString += args[i];
		if (i != args.size() - 1)
			finalString += ' ';
	}
	return (finalString);
}