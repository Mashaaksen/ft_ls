#include "ft_ls.h"

char 		**create_2_args(char *av)
{
	char 	**args;
	char 	**a;
	int 	iter;

	iter = 0;
	args = (char **)malloc(sizeof(char *) * 3);
	if (!ft_strchr(av, '/'))
	{
		args[0] = "./";
		args[1] = av;
	}
	else
	{
		a = ft_strsplit(av, '/');
		args[0] = (*av == '/' ? "/" : "");
		if (*a && a[1])
		{
			while (a[iter] && a[iter + 1])
				args[0] = ft_strjoin(ft_strjoin(args[0], a[iter++]), "/");
			args[1] = a[iter];
		}
		else if (*a && !a[1])
		{
			args[0] = ft_strjoin(a[0], "/");
			args[1] = NULL;
		}
		else
			args[1] = NULL;
	}
	args[2] = NULL;
	return (args);
}

int 		check_right_path(char *av, t_dir *inform, t_path **tmp, t_key *key)
{
	char **args;

	args = create_2_args(av);
	inform->dir = opendir(args[0]);
	if (!inform->dir)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", av);
		return (0);
	}
	else
		while (args[1] && (inform->entry = readdir(inform->dir)))
			if (!ft_strcmp(inform->entry->d_name, args[1]))
			{
				*tmp = (t_path *)malloc(sizeof(t_path));
				(*tmp)->av = av;
				(*tmp)->road = args[0];
				(*tmp)->file = args[1];
				lstat(av, &(*tmp)->buff);
				key->count++;
				if (key->key_time || key->key_list)
					ft_find_time(&((*tmp)->time), (*tmp)->buff);
				if (S_ISDIR((*tmp)->buff.st_mode))
					(*tmp)->type = 'd';
				else
				{
					key->file = 1;
					(*tmp)->type = 'f';
				}
				break;
			}
	if (!args[1])
	{
		*tmp = (t_path *)malloc(sizeof(t_path));
		(*tmp)->av = av;
		(*tmp)->road = args[0];
		(*tmp)->file = args[1];
		(*tmp)->time.month = 13;
		(*tmp)->type = 'd';
		key->count++;
	}
	if (!(*tmp))
	{
		ft_printf("ft_ls: %s: No such file or directory\n", av);
		return (0);
	}
	(*tmp)->next = NULL;
	closedir(inform->dir);
	return (1);
}

int			alpha(char *a, char *b)
{
	char	*s1;
	char	*s2;

	s1 = a;
	s2 = b;
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 > *s2 ? 1 : 0);
		*s1 != '\0' ? s1++ : 0;
		*s2 != '\0' ? s2++ : 0;
	}
	return (0);
}

void 		find_path(t_ls *ls, char **av)
{
	t_path	*tmp;

	ls->path = NULL;
	while (*av)
	{
		tmp = NULL;
		if (check_right_path(*av, &ls->inform, &tmp, &ls->keys))
			add_and_sort(ls->keys, &ls->path, tmp);
		av++;
	}
}
