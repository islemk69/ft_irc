#include "../includes/Utils.hpp"

std::vector<std::string> split(const std::string & msg, const std::string & delim) {
    std::vector<std::string> result;
    std::string::size_type startPos = 0;
    std::string::size_type endPos = msg.find_first_of(delim);

    while (endPos != std::string::npos) {
        result.push_back(msg.substr(startPos, endPos - startPos));
        startPos = endPos + 1; // +1 car chaque caractère dans delim est un délimiteur
        endPos = msg.find_first_of(delim, startPos);
    }

    // Ajoute le dernier élément
    result.push_back(msg.substr(startPos));

    return result;
}
