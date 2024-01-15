#include "../includes/Server.hpp"
#include "../includes/numericReplies.hpp"
#include <string>

Server::Server(std::string port, std::string password){
    if (port.empty() || port.find_first_not_of("0123456789") != std::string::npos) {
		throw std::invalid_argument("Error: Wrong port format");
	}
    std::istringstream iss(port);
    int portNumber;
    //on met le iss dans le port number
    iss >> portNumber;
    if (iss.fail() || portNumber < 1 || portNumber > 65535)
        throw std::invalid_argument("Error wrong port number");
    this->_port = std::atoi(port.c_str());
    if (password.empty())
        throw std::invalid_argument("Password can't be empty");
    this->_password = password;
}

void Server::initServer(){
    this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if (this->_serverSocket == -1) { 
        throw std::runtime_error("Error while creating socket");
    }
    int option = 1;
    setsockopt(this->_serverSocket, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
    sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress)); 
    serverAddress.sin_family = AF_INET; 
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(this->_port); 

    if (bind(this->_serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        close(this->_serverSocket);
        throw std::runtime_error("Error while binding socket and adress");
    }

    if (listen(this->_serverSocket, 20) == -1) {
        close(this->_serverSocket);
        throw std::runtime_error("Error in listen");
    }

    
    this->_fds.push_back(pollfd()); 
    this->_fds[0].fd = this->_serverSocket;
    this->_fds[0].events = POLLIN;
    this->initCommand();
}

void Server::initCommand(){
    this->_cmds["INVITE"] = &inviteCmd;
    this->_cmds["JOIN"] = &joinCmd;
    this->_cmds["KICK"] = &kickCmd;
    this->_cmds["MODE"] = &modeCmd;
    this->_cmds["NICK"] = &nickCmd;
    this->_cmds["PASS"] = &passCmd;
    this->_cmds["PRIVMSG"] = &privmsgCmd;
    this->_cmds["TOPIC"] = &topicCmd;
    this->_cmds["USER"] = &userCmd;
}

int iter = 0; //DEBUG

void Server::execServer(){
    if (poll(&this->_fds[0], this->_fds.size(), -1) == -1) { 
        throw std::runtime_error("Error in poll");
    } 

    if (this->_fds[0].revents & POLLIN) { 
        int fdClient = accept(this->_serverSocket, NULL, NULL); 
        if (fdClient != -1) { 
            Client* newClient = new Client(fdClient);
            std::cout << "Client n " << iter << ", fd ----> " << newClient->fd << std::endl; // DEBUG
            iter++; //DEBUG
            this->_clients[fdClient] = newClient;
            this->_fds.push_back(pollfd()); 
            this->_fds.back().fd = fdClient; 
            this->_fds.back().events = POLLIN; 
        }
    }
    for (size_t i = 1; i < this->_fds.size(); ++i) {
        if (this->_fds[i].revents & POLLIN) {
            this->readClientRequest(i);
        }
    }
    
}

Client* Server::getClientFromFd(int fd) {
    std::map<int, Client*>::iterator it = this->_clients.find(fd);
    if (it != this->_clients.end()) {
        return it->second;
    }
    return NULL;
}

void Server::readClientRequest(int i) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(this->_fds[i].fd, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        perror("Error reading client data");
        close(this->_fds[i].fd);
        this->_fds.erase(this->_fds.begin() + i);
        return ;
    }

    if (bytesRead == 0) {
        close(this->_fds[i].fd);
        this->_fds.erase(this->_fds.begin() + i);
        return ; 
    }
    Server::sendToClient(_fds[i].fd, ERR_NONICKNAMEGIVEN(std::string("Client")));
    //HUGO TU FOUS TON PERSING A PARTIT D'ICI

    Command cmd(buffer);


    if (!cmd.isValid) {
        Server::sendToClient(_fds[i].fd, ERR_UNKNOWNCOMMAND(std::string("Client"), cmd.command));
        return ;
    }
    CmdIt it = this->_cmds.find(cmd.command);

    Client* client = getClientFromFd(this->_fds[i].fd);
    //si on trouve
    if (it != this->_cmds.end()) {
        std::cout << "cmd trouvee :" << cmd.command << std::endl;
        std::cout << cmd << std::endl;

        it->second(client, cmd, this);
    } else {
        Server::sendToClient(client->fd, "pas trouvee");
    }
    //si la commande n'a pas ete trouver 
    //LANCEMENT DES COMMANDES EN FONCTION DE LA COMMANDE DETECTER AVEC fonctionCmd(x, this->_clients[i], x)
}

void Server::sendToClient(int fd, const std::string &content) {
    size_t bytesSent = 0;
    while (bytesSent < content.length()) {
        ssize_t len = send(fd, content.c_str(), content.length(), 0);
        if (len < 0) {
            std::cout << "send() error: " << strerror(errno) << std::endl;
            break ;
        }
        bytesSent += len;
    }
}

// Client *Server::getClientByName(const std::string &name) {
// 	for (clientIt it = this->_clients.begin(); it != this->_clients.end(); it++) {
// 		if (Utils::copyToUpper(name) == Utils::copyToUpper(it->second->nickName)) {
// 			return it->second;
// 		}
// 	}
// 	return NULL;
// }

Channel *Server::getChannelByName(const std::string& name) {
	for (std::map<std::string, Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); it++) {
		if (it->second->getName() == name) {
			return it->second;
		}
	}
	return NULL;
}


Client 		*Server::getClientByNick(const std::string &nick){
    for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
        if (copyToUpper(nick) == copyToUpper(it->second->nick)) {
            return it->second;
        }
    }
	return NULL;
}

void Server::addChannel(Channel *newChannel) {
	this->_channels[newChannel->getName()] = newChannel;
}

bool Server::isNickUsed(Client *client, std::string nick) {
	std::string upperNick = copyToUpper(nick);
	std::transform(nick.begin(), nick.end(), nick.begin(), toupper);
	std::map<int, Client*>::iterator it;
	for (it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (it->second->fd != client->fd && upperNick == copyToUpper(it->second->nick)) {
			return true;
		}
	}
	return false;
}

std::string Server::getPassword()const{
    return this->_password; 
}

int Server::getServerSocket(){return this->_serverSocket;}

Server::~Server(){}
