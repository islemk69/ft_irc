Yo, voilà comment j'ai avancé depuis cette semaine sur le projet et voilà ce que je propose :
- Selon moi ce serait bien de se baser sur la toute première doc d'IRC, la RFC 1459 : https://www.rfc-editor.org/rfc/rfc1459
- Elle est assez facile à lire mais des fois incomplète, notamment sur les codes d'erreur (les "RPL_..." et "ERR_...").
- Si y a des infos dedans qui sont pas claires ou incomplètes, on peut utiliser la doc "Modern IRC" pour compléter : https://modern.ircdocs.horse/

Perso j'ai lu toute la RFC 1459 (en tous cas sur les parties qui sont demandées par le sujet), c'est vraiment utile pour comprendre.




Ensuite pour la partie code, ils donnent une archive "bircd.tar.gz" avec le sujet, elle contient un serveur IRC en C.
J'ai commit un dossier "bircd" où j'ai commenté un maximum de fonctions un peu compliquées sur le setup du serveur, les sockets, les fd, ...
J'ai aussi mis dans le dossier des screens des explications de Phind pour certaines fonctions au cas où.
Il manque la fonction "client_write" qui est vide, du coup le serveur se lance mais on peut pas envoyer de messages.

Du coup je pense qu'on peut se diviser le travail comme ça :
- Un sur la partie "Parsing" (vérifier que les commandes envoyées sont au bon format et retourner la bonne erreur (voir les deux docs pour savoir quelle erreur retourner dans quel cas).
- Un sur la partie "Client et Commandes", qui gèrerait l'envoi des commandes et des messages, la gestion de channels etc.
- Un sur la partie "Networking", qui gèrerait toute la partie technique (sockets, file descriptors, ...).

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

informations globales sur l'utilisaiton du projet (SURTOUT POUR HDAMITZI PARSING) :

1) connection du client sur le serveur (générlement le port 6667) 
./ircserv <port> <password>

si connection ok le client doit envoyer un message d'authentification au serveur qui est :

NICK mon_surnom
USER mon_nom_utilisateur 0 * : #Mon Nom Réel <username> <mode> <unused> <realname>. avec le mode qui n'est plus utiliser dans irc moderne donc on met 0 balek. pareil pour * qui 
                                veu dire UNUSUED il est la par défaut il faut les ignorer dans le parsing mais apparement elles doivent etre presente quand meme dans un prot. IRC

2) rejoindre un cannal :

JOIN #nom_du_canal #pas compliqué

3)Envoie des messages :

PRIVMSG #nom_du_canal :Bonjour à tous !
je ne sait pas si il faut implementer message privé hors canna lentre user.

4) commande de l'operateur (operateur = admin ou moderateur)

KICK #nom_du_canal utilisateur_a_expulser :Raison de l'expulsion
MODE #nom_du_canal +o utilisateur_opérateur
TOPIC #nom_du_canal :Nouveau sujet du canal

5) quitter un cannal : 
QUIT :Raison de la déconnexion

