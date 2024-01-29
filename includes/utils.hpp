/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:35:40 by ikaismou          #+#    #+#             */
/*   Updated: 2024/01/26 15:07:21 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "Server.hpp"

std::vector<std::string>	ft_split(const std::string &msg, const std::string &delim);
std::vector<std::string>	ft_split2(std::string &msg, const std::string &delim);
std::string					copyToUpper(std::string src);
std::string					joinStr(std::vector<std::string> args);

#endif