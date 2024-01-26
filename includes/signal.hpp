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
