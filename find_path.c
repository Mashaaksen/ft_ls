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

void 		check_right_path(char *av, t_dir *inform)
{
	char **args;
	struct stat buff;
	int flag;

	flag = 0;
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
				lstat(av, &buff);
				flag = 1;
				break;
			}
	if (!flag)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", av);
		exit(0);
	}
	closedir(inform->dir);
}

void 		find_path(t_ls *ls, char **av)
{
	while (av)
	{
		check_right_path(*av, &ls->inform);
		av++;
	}
}

