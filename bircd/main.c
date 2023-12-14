
#include "bircd.h"

int	main(int ac, char **av)
{
  t_env	e;

  init_env(&e); // alloue et init le tableau de t_fd.
  get_opt(&e, ac, av); // parsing des arguments.
  srv_create(&e, e.port); // demarrage du serveur tcp/ip.
  main_loop(&e);
  return (0);
}
