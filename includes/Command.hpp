#ifndef COMMAND_HPP
# define COMMAND_HPP
# include <ostream>
# include <vector>
class Command
{
	public:
		Command(std::string msg);
		Command();
		~Command();

		bool isValid;
		std::string command;
		std::vector<std::string> args;

		static bool isAllCaps(const std::string& str) ;

};

std::ostream &operator<<(std::ostream &os, const Command &c);

#endif
