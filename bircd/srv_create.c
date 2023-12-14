
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include "bircd.h"

void			srv_create(t_env *e, int port)
{
  int			s;
  struct sockaddr_in	sin;
  struct protoent	*pe;
  
  pe = (struct protoent*)Xv(NULL, getprotobyname("tcp"), "getprotobyname"); // stocke le protocole tcp dans pe.
  s = X(-1, socket(PF_INET, SOCK_STREAM, pe->p_proto), "socket"); // crée un socket tcp/ipv4 et stocke son fd dans s.
  sin.sin_family = AF_INET; // déclare que le serveur sera en ipv4.
  sin.sin_addr.s_addr = INADDR_ANY; // déclare que n'importe quelle ip peut se connecter.
  sin.sin_port = htons(port); // stocke le port (en passant par htons pour formater correctement l'int).
  X(-1, bind(s, (struct sockaddr*)&sin, sizeof(sin)), "bind"); // lie le socket et les informations de sockaddr_in.
  X(-1, listen(s, 42), "listen"); // indique au serveur qu'il doit être prêt à recevoir des connexions (42 max simultanément).
  e->fds[s].type = FD_SERV; // le fd correspondant au socket est indiqué comme de type serveur.
  e->fds[s].fct_read = srv_accept; // la fonction read de ce fd sera srv_accept.
}
