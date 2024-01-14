#include "../includes/Server.hpp"

void printLoadingAnimation() {
    const char* animationChars = ".oOo";
    const int numFrames = 4;
    const int numDots = 20;

    for (int i = 0; i < numDots; ++i) {
        std::cout << animationChars[i % numFrames] << " ";
        std::cout.flush();
        usleep(100000); 
        std::cout << "\b\b  \b";
    }
    std::cout << std::endl;
    std::cout.flush();
}

int main(int argc, char **argv) {
    if (argc != 3)
        return (std::cerr << RED << "Usage: ./ircserv <port> <password>" << DEFAULT << std::endl, 1);
    std::string password = argv[2];
    std::string port = argv[1];
    try {
        Server server(port, password);
        std::cout << YELLOW << "Launching irc server...." << DEFAULT << std::endl;
        server.initServer();
        printLoadingAnimation();
        std::cout << GREEN << "IRC server Launched" << DEFAULT << std::endl;
        while (true) {
            server.execServer();
        }
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
