/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:27:26 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/29 13:27:27 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_HPP
# define COMMAND_HPP
# include <ostream>
# include <vector>
class Command
{
	public:
		Command(std::string msg);
		Command();
		~Command();

		bool isValid;
		std::string command;
		std::vector<std::string> args;

		static bool isAllCaps(const std::string& str) ;

};

std::ostream &operator<<(std::ostream &os, const Command &c);

#endif
