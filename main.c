#include "ft_ls.h"

int 		main(int ac, char **av)
{
	t_ls	ls;

	ac = 0;
	av++;
	find_keys(&ls, &av);
	find_path(&ls, av);
	ft_ls(ls.path, ls.keys, 0);
}
