
#include <string.h>
# include <sys/select.h>
#include "bircd.h"

void	init_fd(t_env *e)
{
  int	i;

  i = 0;
  e->max = 0;
  FD_ZERO(&e->fd_read); // clear les sets de fd.
  FD_ZERO(&e->fd_write);
  while (i < e->maxfd)
  {
    if (e->fds[i].type != FD_FREE) // si le fd est utilisé,
    {
      FD_SET(i, &e->fd_read); // l'ajoute dans le set des fd depuis lesquels on va lire.
      if (strlen(e->fds[i].buf_write) > 0) // si le buffer n'est pas vide,
      {
        FD_SET(i, &e->fd_write); // l'ajoute dans le set des fd dans lesquels on va écrire.
      }
      e->max = MAX(e->max, i); // stocke le fd max utilisé.
    }
    i++;
  }
}
