#include <iostream>
#include "server.hpp"


int main(){
    std::cout << "yo" << std::endl;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //création du socket AF_INET = ipv4 SOCK_STREAM = TCP
    if (serverSocket == -1)
        return (perror("Error while creating socket\n"), 1);
    sockaddr_in serverAddress; //creation adresse ipv4
    serverAddress.sin_family = AF_INET; //configuration adresse en ipv4;
    serverAddress.sin_addr.s_addr = INADDR_ANY;  // Accepter les connexions de n'importe quelle adresse
    serverAddress.sin_port = htons(PORT);       // Le numéro de port que vous avez spécifié lors du lancement du serveur
    if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) // lier le socket a ladresse ipv4 cree
        return(perror("Error when biding socket"), 1);
    listen(serverSocket, 20);  // BACKLOG est la taille maximale de la file d'attente de connexions en attente
    while (true) {
        int clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("Erreur lors de l'acceptation de la connexion");
            continue;
        }
        char buffer[1024];
        memset(buffer, 0, sizeof(buffer));

        ssize_t bytesRead;
        while ((bytesRead = read(clientSocket, buffer, sizeof(buffer))) > 0) {
            // Traiter les données lues ici (par exemple, les afficher)
            std::cout << "Client says: " << buffer << std::endl;

            // Répondre au client
            const char* response = "Hello from server!";
            ssize_t bytesSent = write(clientSocket, response, strlen(response));
            if (bytesSent == -1) {
                perror("Erreur lors de l'envoi de données au client");
            }

            // Effacer le tampon pour la prochaine itération
            memset(buffer, 0, sizeof(buffer));
        }
        if (bytesRead == -1) {
            perror("Erreur lors de la lecture des données du client");
        }
        // Fermer la connexion du client
        close(clientSocket);
    }
    return (0);
}