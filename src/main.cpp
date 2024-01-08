#include <iostream>
#include "server.hpp"


// int main(){
//     std::cout << "yo" << std::endl;
//     int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //création du socket AF_INET = ipv4 SOCK_STREAM = TCP
//     if (serverSocket == -1)
//         return (perror("Error while creating socket\n"), 1);
//     sockaddr_in serverAddress; //creation adresse ipv4
//     serverAddress.sin_family = AF_INET; //configuration adresse en ipv4;
//     serverAddress.sin_addr.s_addr = INADDR_ANY;  // Accepter les connexions de n'importe quelle adresse
//     serverAddress.sin_port = htons(PORT);       // Le numéro de port que vous avez spécifié lors du lancement du serveur
//     if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) // lier le socket a ladresse ipv4 cree
//         return(perror("Error when biding socket"), 1);
//     listen(serverSocket, 20);  // BACKLOG est la taille maximale de la file d'attente de connexions en attente
//     while (true) {
//         int clientSocket = accept(serverSocket, NULL, NULL);
//         if (clientSocket == -1) {
//             perror("Erreur lors de l'acceptation de la connexion");
//             continue;
//         }
//         char buffer[1024];
//         memset(buffer, 0, sizeof(buffer));

//         ssize_t bytesRead;
//         while ((bytesRead = read(clientSocket, buffer, sizeof(buffer))) > 0) {
//             // Traiter les données lues ici (par exemple, les afficher)
//             std::cout << "Client says: " << buffer << std::endl;

//             // Répondre au client
//             const char* response = "Hello from server!";
//             ssize_t bytesSent = write(clientSocket, response, strlen(response));
//             if (bytesSent == -1) {
//                 perror("Erreur lors de l'envoi de données au client");
//             }

//             // Effacer le tampon pour la prochaine itération
//             memset(buffer, 0, sizeof(buffer));
//         }
//         if (bytesRead == -1) {
//             perror("Erreur lors de la lecture des données du client");
//         }
//         // Fermer la connexion du client
//         close(clientSocket);
//     }
//     return (0);
// }

int main() {
    std::cout << "yo" << std::endl;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //création du socket AF_INET = ipv4 SOCK_STREAM = TCP, valaur inutile en irc moderne par default 0 
    if (serverSocket == -1) { //gestion d'erreur stop si erreur
        perror("Error while creating socket");
        return 1;
    }

    sockaddr_in serverAddress; //bibliotheque netinet stockage de l'adresse du serveur j'ai check le bibli c'est une struct basique
    memset(&serverAddress, 0, sizeof(serverAddress)); //jmet tout a zerowwww
    //parametrage et ajout des valeurs
    serverAddress.sin_family = AF_INET; //la je lui dit t'es en mode ipv4
    serverAddress.sin_addr.s_addr = INADDR_ANY; //j'autorise toutes les connections
    serverAddress.sin_port = htons(PORT); //je lui dit d'utiliser le port 6667

    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        perror("Error when binding socket");
        close(serverSocket);
        return 1;
    } // liaison du socket a l'adresse crée precedemment

    if (listen(serverSocket, 20) == -1) {
        perror("Error in listen");
        close(serverSocket);
        return 1;
    } //mode ecoute activeyy bien sur on secure tt ca

    std::vector<pollfd> fds; //tableaude fd tout pret avec la bibli poll.h
    fds.push_back(pollfd()); // la j'ajoute ma premiere struct dans mon vecteur chques struct contient ces varaibles : struct pollfd {
                                                                                                               //         int   fd;         descripteur de fichier detecte
                                                                                                              //          short events;     event detecte
                                                                                                               //         short revents;    evenement detecter qui est retourner par poll
                                                                                                               //     };
    fds[0].fd = serverSocket; //jmet en surveillance le socket le qui est le tout premier fd
    fds[0].events = POLLIN; //jmet son event en POLLIN = surveiller levenement
    //fd[0] represente le socket serveur, apartir de fd[n + 1 ...] c'est les sockets clients.
    while (true) {

        
        if (poll(&fds[0], fds.size(), -1) == -1) { 
            perror("Error in poll");
            break;
        } // a chaquees debut de boucle je check si un nouvel evenement est detecté sur le socket serveur ET les sockets clients le 3 eme parametre represente le temps en ms -1 = infini
        //poll ici va mettre fds[0].revent a POLLIN si un client tente de se connecter !

        if (fds[0].revents & POLLIN) { //si un client tente de se connecter
            // nouvelle connexion
            int fdClient = accept(serverSocket, NULL, NULL); //nouveau client creation de son fd
            if (fdClient != -1) { //securiter si accept n'a pas fail.
                fds.push_back(pollfd()); //j'ajoute une nouvelle structure a 0 à la fin de fds
                fds.back().fd = fdClient; // je fou le fd dans la struct
                fds.back().events = POLLIN; //pareil je le met en POLLIN pour surveiller ses events
            }
        }
        //envent = nouvel evenement detecte / revent = donne a lire sur le fd
        for (size_t i = 1; i < fds.size(); ++i) { //iterations dans tout les fd client (n + 1)
            if (fds[i].revents & POLLIN) {
                // donnés clients
                char buffer[1024];
                memset(buffer, 0, sizeof(buffer));
                ssize_t bytesRead = read(fds[i].fd, buffer, sizeof(buffer));
                if (bytesRead == -1) {
                    perror("Error reading client data");
                    close(fds[i].fd);
                    fds.erase(fds.begin() + i);
                    continue;
                }
                //dans la doc read renvoie 0 si le client se déco donc :
                if (bytesRead == 0) {
                    close(fds[i].fd); //je ferme son fd
                    fds.erase(fds.begin() + i); //je le supprime du container
                    continue; //je reprend ma boucle ya r a print ou ecrire dans le fd !
                }
                // a partir de la il faut traiter les commandes et les parser
                std::cout << "Client says: " << buffer << std::endl;
                const char* response = "Hello from server!";
                ssize_t bytesSent = write(fds[i].fd, response, strlen(response));
                if (bytesSent == -1) {
                    perror("Error sending data to client");
                }
            }
        }
    }
    close(serverSocket);
    return 0;
}