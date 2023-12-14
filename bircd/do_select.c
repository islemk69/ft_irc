
#include <stdlib.h>
#include "bircd.h"

void	do_select(t_env *e)
{
  e->r = select(e->max + 1, &e->fd_read, &e->fd_write, NULL, NULL);
}

// select attend pour un fd disponible pour de la lecture, et un pour l'écriture.
// une fois trouvés, il supprime tous les autres fd du set.
// params : 
// - le numéro du fd max utilisé + 1
// - l'adresse du set de fd de lecture
// - l'adresse du set de fd d'écriture
// - l'adresse du set de fd pour les exceptions (NULL)
// - l'adresse d'une struct timeval pour le timeout.