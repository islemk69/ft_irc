#include "../includes/signal.hpp"

bool sig::stopServer = false;

void sig::signalHandler(int signum) {
    if (signum == SIGINT)
        sig::stopServer = true;
}