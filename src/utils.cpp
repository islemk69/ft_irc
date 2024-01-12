/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:37:11 by ikaismou          #+#    #+#             */
/*   Updated: 2024/01/12 16:18:52 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

std::vector<std::string>	ft_split(std::string str, char sep)
{
	std::size_t					pos;
	std::string					token;
	std::vector<std::string>	vec;

	if (str.empty())
		return vec;
	while ((pos = str.find(sep)) != std::string::npos)
	{
		token = str.substr(0, pos);
		vec.push_back(token);
		str.erase(0, pos + 1);
	}
	return vec;
}


std::string copyToUpper(std::string src){
    std::string res = src;
	std::transform(src.begin(), src.end(), src.begin(), toupper);
	return res;
}