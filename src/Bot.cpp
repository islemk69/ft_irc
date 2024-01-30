#include "../includes/Bot.hpp"

int main(int argc, char **argv) {
	if (argc != 4){
		 std::cerr << "Error: Unable to create IRC bot" << std::endl;
		 return 1;
	}
    Bot bot(argv[1], argv[2], argv[3]);
    if (bot.isConnected()) {
        bot.run();
    } else {
        std::cerr << "Error: Unable to create IRC bot\n";
        return 1;
    }
    return 0;
}