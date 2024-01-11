#include "../includes/Server.hpp"
#include <string>

Server::Server(std::string port, std::string password){
    this->_port = std::atoi(port.c_str());
    if (password[0])
        this->_password = password;
}

void Server::initServer(){
    this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0); 
    if (this->_serverSocket == -1) { 
        throw std::runtime_error("Error while creating socket");
    }

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
            std::cout << "Client n " << iter << ", fd ----> " << newClient->getClientFd() << std::endl; // DEBUG
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

void Server::readClientRequest(int i){
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
    std::cout << "Client says: " << buffer << std::endl;
    Server::sendToClient(_fds[i].fd, ERR_NONICKNAMEGIVEN(std::string("Client")));
    //HUGO TU FOUS TON PERSING A PARTIT D'ICI
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

std::string copyToUpper(std::string src){
    std::string res = src;
	std::transform(src.begin(), src.end(), src.begin(), toupper);
	return res;
}

Client 		*Server::getClientByNick(const std::string &nick){
    	for (std::map<int, Client*>::iterator it = this->_clients.begin(); it != this->_clients.end(); it++) {
		if (copyToUpper(nick) == copyToUpper(it->second->nickName)) {
			return it->second;
		}
	}
	return NULL;
}

int Server::getServerSocket(){return this->_serverSocket;}

Server::~Server(){}