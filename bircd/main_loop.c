
#include "bircd.h"

void	main_loop(t_env *e)
{
  while (1)
    {
      init_fd(e); // initialise/actualise les sets de fd et y ajoute les fd de lecture et d'écriture utilisés.
      do_select(e); // stocke dans e->r le nombre de fd conservés par select.
      check_fd(e); // monitore les fd : nouvelle connexion ou envoi/réception de message.
    }
}
