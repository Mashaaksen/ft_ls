#include "ft_ls.h"

void		add_keys(t_key **key, char c)
{
	t_key	*tmp;
	t_key	*p;

	p = (t_key *)malloc(sizeof(t_key));
	p->s = c;
	p->next = NULL;
	if (*key == NULL)
		*key = p;
	else
	{
		tmp = *key;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = p;
	}
}

void		check_keys(char *str, t_key **key)
{
	while (*str)
	{
		*str == '-' ? str++ : 0;
		if (*str != 'l' && *str != 'R' && *str != 'a' && *str != 'r' && *str != 't')
			error_option(*str);
		add_keys(key, *str);
		str++;
	}
}

void		add_path(char *str, t_path **path)
{
	t_path	*tmp;
	t_path	*p;
	DIR		*dir;

	p = (t_path *)malloc(sizeof(t_path));
	p->str = ft_strdup(str);
	p->next = NULL;
	if ((dir = opendir(str)) == NULL)
	{
		perror(str);
		return ;
	}
	closedir(dir);
	if (*path == NULL)
		*path = p;
	else
	{
		tmp = *path;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = p;
	}
}

void		ft_keys(char **av, t_key **key, t_path **path, int *len)
{
	int 	i;

	i = 1;
	*len = 0;
	*path = NULL;
	while (av[i] != NULL && *av[i] == '-')
		check_keys(av[i++], key);
	while (av[i] != NULL)
	{
		add_path(av[i++], path);
		(*len)++;
	}
	if (*path == NULL)
	{
		add_path(".", path);
		(*len)++;
	}
}
