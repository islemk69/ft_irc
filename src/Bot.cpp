#include "../includes/Bot.hpp"



int main(int argc, char **argv) {
	if (argc != 2)
		 std::cerr << "Error: Unable to create IRC bot" << std::endl;
    Bot bot(argv[1]);
    if (bot.isConnected()) {
        bot.run();
    } else {
        std::cerr << "Error: Unable to create IRC bot\n";
        return 1;
    }

    return 0;
}
