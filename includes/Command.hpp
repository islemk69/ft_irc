#ifndef COMMAND_HPP
# define COMMAND_HPP

class Command
{
	public:
		Command(std::string msg);
		Command();
		~Command();

		bool isValid;
		std::string command;
		std::vector<std::string> args;
};

std::ostream &operator<<(std::ostream &os, const Command &c);

#endif
