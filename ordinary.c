#include "ft_ls.h"

int			find_time(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 't')
			return (1);
		key = key->next;
	}
	return (0);
}

int			find_l(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 'l')
			return (1);
		key = key->next;
	}
	return (0);
}

int 		recursion(t_name *names)
{
	while (names->next != NULL)
		names = names->next;
	if (names->tipe == 'd' && *names->str != '.')
		return(1);
	return(0);
}

void		create_tmp(t_path **tmp, char *str, t_name *name)
{
	while (name != NULL)
	{
		if (name->tipe == 'd' && *(name->str) != '.')
			add_path(ft_strjoin(str, name->str), tmp);
		name = name->next;
	}
}

void		ordinary(t_key *key, t_path *path, int len, int rec)
{
	char 	*str;
	t_ls	*ls;
	t_path	*tmp;
	int		flag;
	int 	total;
	int 	a;

	a = find_a(key);
	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->names = NULL;
	total = 0;
	flag = (path->next == NULL && rec == 0) ? 0 : 1;
	flag == 0 && len > 1 ? flag = 1 : 0;
	while (path != NULL)
	{
		tmp = NULL;
		if (flag == 1 && ft_strcmp(path->str, "."))
			printf("%s:\n", path->str);
		str = ft_strjoin(path->str, "/");
		ls->dir = opendir(str);
		while ((ls->entry = readdir(ls->dir)) != NULL)
		{
			stat(ft_strjoin(str, ls->entry->d_name), &ls->buff);
			//total += ls->buff.st_blocks;
			ft_name(&ls->names, ls);
			if (*(ls->entry->d_name) != '.' || a == 1)
				total += ls->buff.st_blocks;
		}
		if (find_time(key) == 0)
			ft_alpha_sort(&ls->names);
		else
			ft_time_sort(&ls->names);
		rec == 1 ? create_tmp(&tmp, str, ls->names) : 0;
		free(str);
		printf("total %i\n", total);
		ft_print(ls, find_l(key) == 1 ? 1 : 0, key);
		(rec == 1 && tmp != NULL) ? ordinary(key, tmp, 0, rec) : 0;
		path = path->next;
	}
}
