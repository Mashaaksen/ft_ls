#include "ft_ls.h"

int 		main(int ac, char **av)
{
	t_ls	ls;

	av++;
	find_keys(&ls, &av);
	find_path(&ls, av);
}
