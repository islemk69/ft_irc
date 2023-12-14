
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "bircd.h"

void			srv_accept(t_env *e, int s)
{
  int			cs;
  struct sockaddr_in	csin;
  socklen_t		csin_len;

  csin_len = sizeof(csin);
  cs = X(-1, accept(s, (struct sockaddr*)&csin, &csin_len), "accept"); // accept detecte une connexion sur le serveur (s) et stocke dans csin l'adresse du client.
  printf("New client #%d from %s:%d\n", cs,
	 inet_ntoa(csin.sin_addr), ntohs(csin.sin_port)); // print le fd, l'ip et le port du client.
  clean_fd(&e->fds[cs]);
  e->fds[cs].type = FD_CLIENT; // ce fd est un type client.
  e->fds[cs].fct_read = client_read;
  e->fds[cs].fct_write = client_write;
}
