#include "ft_ls.h"

void 		find_keys(t_ls *ls, char ***av)
{
	ls->keys.key_all = 0;
	ls->keys.key_list = 0;
	ls->keys.key_recurs = 0;
	ls->keys.key_rev = 0;
	ls->keys.key_time = 0;
	while (**av && (**av)[0] == '-')
	{
		if ((**av)[1] != 'l' && (**av)[1] != 'R' && (**av)[1] != 'a' && (**av)[1] != 'r' && (**av)[1] != 't')
		{
			ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-lraRt] [file ...]\n", (*av)[1]);
			exit(0);
		}
		if ((**av)[1] == 'l')
			ls->keys.key_list = 1;
		if ((**av)[1] == 'r')
			ls->keys.key_rev = 1;
		if ((**av)[1] == 'R')
			ls->keys.key_recurs = 1;
		if ((**av)[1] == 'a')
			ls->keys.key_all = 1;
		if ((**av)[1] == 't')
			ls->keys.key_time = 1;
		(*av)++;
	}
}