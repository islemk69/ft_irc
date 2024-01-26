/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikaismou <ikaismou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 15:35:40 by ikaismou          #+#    #+#             */
/*   Updated: 2024/01/12 16:19:02 by ikaismou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "Server.hpp"

std::vector<std::string>	ft_split(const std::string & msg, const std::string & delim, int flg);
std::vector<std::string> ft_split2(std::string &msg, const std::string &delim, int flg);
std::string					copyToUpper(std::string src);

#endif