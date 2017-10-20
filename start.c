#include "ft_ls.h"

int			main(int ac, char **av)
{
	t_ls	ls;
	struct winsize win;

	ac = 0;
	av++;
	find_keys(&ls, &av);
	if (!ls.keys.key_one && !ls.keys.key_list)
	{
		ioctl(0, TIOCGWINSZ, &win);
		win.ws_col = 181;
		ls.keys.ws_col = &win.ws_col;

	}
	find_path(&ls, av);
	ft_ls(ls.path, ls.keys, 0, NULL);
}