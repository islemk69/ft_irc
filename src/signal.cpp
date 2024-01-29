/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccrottie <ccrottie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 13:28:42 by ccrottie          #+#    #+#             */
/*   Updated: 2024/01/29 13:28:43 by ccrottie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signal.hpp"

bool sig::stopServer = false;

void sig::signalHandler(int signum) {
    if (signum == SIGINT)
        sig::stopServer = true;
}