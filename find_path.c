#include "ft_ls.h"

char 		**create_2_args(char *av)
{
	char 	**args;
	char 	**a;
	int 	i;

	i = 0;
	args = (char **)malloc(sizeof(char *) * 3);
	if (!ft_strchr(av, '/'))
	{
		args[0] = "./";
		args[1] = av;
	}
	else
	{
		a = ft_strsplit(av, '/');
		args[0] = "";
		while (a[i] && a[i+1])
			args[0] = ft_strjoin(ft_strjoin(args[0], a[i++]), "/");
		args[1] = ft_strdup(a[i]);
	}
	args[2] = NULL;
	return (args);
}

void 		check_right_path(char *av, t_dir *inform, t_path **tmp)
{
	char **args;

	args = create_2_args(av);
	inform->dir = opendir(args[0]);
	if (!inform->dir)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", av);
		exit(0);
	}
	else
		while ((inform->entry = readdir(inform->dir)))
			if (!ft_strcmp(inform->entry->d_name, args[1]))
			{
				*tmp = (t_path *)malloc(sizeof(t_path));
				(*tmp)->av = av;
				(*tmp)->road = args[0];
				(*tmp)->file = args[1];
				lstat(av, &(*tmp)->buff);
				break;
			}
	if (!(*tmp))
	{
		ft_printf("ft_ls: %s: No such file or directory\n", av);
		exit(0);
	}
	closedir(inform->dir);
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

void 		add_and_sort(t_key keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	if (*path == NULL)
		*path = tmp;
	else
	{
		if (keys.key_time == 0)
		{
			if (keys.key_rev == 0)
			{
				head = *path;
				while (alpha((*path)->av, tmp->av))
				{

				}
			}
		}
	}
}

void 		find_path(t_ls *ls, char **av)
{
	t_path	*tmp;

	ls->path = NULL;
	while (av)
	{
		tmp = NULL;
		check_right_path(*av, &ls->inform, &tmp);
		add_and_sort(ls->keys, &ls->path, tmp);
		av++;
	}
}

