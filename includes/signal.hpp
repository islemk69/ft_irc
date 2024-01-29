/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:27:48 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/29 13:27:49 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_HPP
# define SIGNAL_HPP

# include <csignal>
# include "Server.hpp"

namespace sig
{
    extern bool stopServer;
    void signalHandler(int signum);
}

#endif
