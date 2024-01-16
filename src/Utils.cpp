#include "../includes/Utils.hpp"

std::vector<std::string> split(const std::string & msg, const std::string & delim) {
    std::vector<std::string> res;
    std::string token = "";
    for (int i = 0; i < msg.size(); i++) {
        bool flag = true;
        for (int j = 0; j < delim.size(); j++) {
            if (msg[i + j] != delim[j]) flag = false;
        }
        if (flag) {
            if (token.size() > 0) {
                res.push_back(token);
                token = "";
                i += delim.size() - 1;
            }
        } else {
            token += msg[i];
        }
    }
    res.push_back(token);
    std::cout << "split" <<res.size() << std::endl;
    return (res);
}
