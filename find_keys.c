#include "ft_ls.h"

void 		find_keys(t_ls *ls, char ***av)
{
	ls->keys.key_all = 0;
	ls->keys.key_list = 0;
	ls->keys.key_recurs = 0;
	ls->keys.key_rev = 0;
	ls->keys.key_time = 0;
	ls->keys.count = 0;
	ls->keys.file = 0;
	while (**av && (**av)[0] == '-' && (**av)[1])
	{
		(**av)++;
		while (***av)
		{
			if (***av != 'l' && ***av != 'R' && ***av != 'a' && ***av != 'r' && ***av != 't')
			{
				ft_printf("ft_ls: illegal option -- %c\nusage: ft_ls [-lraRt] [file ...]\n", ***av);
				exit(0);
			}
			if (***av == 'l')
				ls->keys.key_list = 1;
			if (***av == 'r')
				ls->keys.key_rev = 1;
			if (***av == 'R')
				ls->keys.key_recurs = 1;
			if (***av == 'a')
				ls->keys.key_all = 1;
			if (***av == 't')
				ls->keys.key_time = 1;
			(**av)++;
		}
		(*av)++;
	}
}