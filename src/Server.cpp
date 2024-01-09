#include "Server.hpp"
#include <string>

Server::Server(std::string port, std::string password){
    this->_port = std::atoi(port.c_str());
    if (password[0])
        this->_password = password;
}

void Server::initServer(){
    this->_serverSocket = socket(AF_INET, SOCK_STREAM, 0); //création du socket AF_INET = ipv4 SOCK_STREAM = TCP, valaur inutile en irc moderne par default 0 
    if (this->_serverSocket == -1) { //gestion d'erreur stop si erreur
        throw std::runtime_error("Error while creating socket");
    }

    sockaddr_in serverAddress; //bibliotheque netinet stockage de l'adresse du serveur j'ai check le bibli c'est une struct basique
    memset(&serverAddress, 0, sizeof(serverAddress)); //jmet tout a zerowwww
    //parametrage et ajout des valeurs
    serverAddress.sin_family = AF_INET; //la je lui dit t'es en mode ipv4
    serverAddress.sin_addr.s_addr = INADDR_ANY; //j'autorise toutes les connections
    serverAddress.sin_port = htons(this->_port); //je lui dit d'utiliser le port 6667

    if (bind(this->_serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        close(this->_serverSocket);
        throw std::runtime_error("Error while binding socket and adress");
    } // liaison du socket a l'adresse crée precedemment

    if (listen(this->_serverSocket, 20) == -1) {
        close(this->_serverSocket);
        throw std::runtime_error("Error in listen");
    } //mode ecoute activeyy bien sur on secure tt ca

     //tableaude fd tout pret avec la bibli poll.h
    this->_fds.push_back(pollfd()); // la j'ajoute ma premiere struct dans mon vecteur chques struct contient ces varaibles : struct pollfd {
                                                                                                               //         int   fd;         descripteur de fichier detecte
                                                                                                              //          short events;     event detecte
                                                                                                               //         short revents;    evenement detecter qui est retourner par poll
                                                                                                               //     };
    this->_fds[0].fd = this->_serverSocket; //jmet en surveillance le socket le qui est le tout premier fd
    this->_fds[0].events = POLLIN; //jmet son event en POLLIN = surveiller levenement
    //fd[0] represente le socket serveur, apartir de fd[n + 1 ...] c'est les sockets clients.

}

int iter = 0; //DEBUG

void Server::launchServer(){
    if (poll(&this->_fds[0], this->_fds.size(), -1) == -1) { 
        throw std::runtime_error("Error in poll");
    } // a chaquees debut de boucle je check si un nouvel evenement est detecté sur le socket serveur ET les sockets clients le 3 eme parametre represente le temps en ms -1 = infini
        //poll ici va mettre this->_fds[0].revent a POLLIN si un client tente de se connecter !

    if (this->_fds[0].revents & POLLIN) { //si un client tente de se connecter
        // nouvelle connexion
        int fdClient = accept(this->_serverSocket, NULL, NULL); //nouveau client creation de son fd
        if (fdClient != -1) { //securiter si accept n'a pas fail.
            Client* newClient = new Client(fdClient);
            std::cout << "Client n " << iter << ", fd ----> " << newClient->getClientFd() << std::endl; // DEBUG
            iter++; //DEBUG
            this->_clients[fdClient] = newClient;
            this->_fds.push_back(pollfd()); //j'ajoute une nouvelle structure a 0 à la fin de this->_fds
            this->_fds.back().fd = fdClient; // je fou le fd dans la struct
            this->_fds.back().events = POLLIN; //pareil je le met en POLLIN pour surveiller ses events
        }
    }
    //envent = nouvel evenement detecte / revent = donne a lire sur le fd
    for (size_t i = 1; i < this->_fds.size(); ++i) { //iterations dans tout les fd client (n + 1)
        if (this->_fds[i].revents & POLLIN) {
            // donnés clients
            char buffer[1024];
            memset(buffer, 0, sizeof(buffer));
            ssize_t bytesRead = read(this->_fds[i].fd, buffer, sizeof(buffer));
            if (bytesRead == -1) {
                perror("Error reading client data");
                close(this->_fds[i].fd);
                this->_fds.erase(this->_fds.begin() + i);
                continue;
            }
            //dans la doc read renvoie 0 si le client se déco donc :
            if (bytesRead == 0) {
                close(this->_fds[i].fd); //je ferme son fd
                this->_fds.erase(this->_fds.begin() + i); //je le supprime du container
                continue; //je reprend ma boucle ya r a print ou ecrire dans le fd !
            }
            // a partir de la il faut traiter les commandes et les parser
            std::cout << "Client says: " << buffer << std::endl;
            const char* response = "Hello from server!";
            ssize_t bytesSent = write(this->_fds[i].fd, response, strlen(response));
            if (bytesSent == -1) {
                perror("Error sending data to client");
            }
        }
    }
}

int Server::getServerSocket(){return this->_serverSocket;}

Server::~Server(){}