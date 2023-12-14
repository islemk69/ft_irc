
#include "bircd.h"

void	check_fd(t_env *e)
{
  int	i;

  i = 0;
  while ((i < e->maxfd) && (e->r > 0)) // on parcourt tous les fd tant que des fd sont disponibles (ceux retournés par select).
    {
      if (FD_ISSET(i, &e->fd_read)) // si le fd de lecture n'a pas été supprimé du set par select,
	e->fds[i].fct_read(e, i); // !! si c'est la première fois que la fonction est appelée, c'est srv_accept qui est appelée pour accepter la connexion d'un client. !! 
      if (FD_ISSET(i, &e->fd_write)) // si le fd d'écriture n'a pas été supprimé du set par select,
	e->fds[i].fct_write(e, i);
      if (FD_ISSET(i, &e->fd_read) || // si les fd de lecture et/ou d'écriture ont été utilisés,
	  FD_ISSET(i, &e->fd_write))
	e->r--;
      i++;
    }
}
