
#include <stdlib.h>
#include <sys/resource.h>
#include "bircd.h"

void		init_env(t_env *e)
{
  int		i;
  struct rlimit	rlp;

  X(-1, getrlimit(RLIMIT_NOFILE, &rlp), "getrlimit"); // stocke dans rlp le nombre de fd disponibles.
  e->maxfd = rlp.rlim_cur;
  e->fds = (t_fd*)Xv(NULL, malloc(sizeof(*e->fds) * e->maxfd), "malloc"); // alloue t_fd * le nombre de fd disponibles.
  i = 0;
  while (i < e->maxfd)
    {
      clean_fd(&e->fds[i]); // init les t_fd à nul.
      i++;
    }
}
