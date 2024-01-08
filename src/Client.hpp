#include "Client.cpp"

class Client {
    private:
        int         _clientfd;
    public:
        bool		hasPassword;
        std::string nickName;
        std::string userName;
        std::string realName;
        std::string previousNickname;
        std::string socketBuffer;
        std::string awayMessage;
};