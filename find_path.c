/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 19:25:17 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/15 19:25:18 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_2_args(char *av, char **road, char **file)
{
	*road = NULL;
	*file = NULL;
	if (!ft_strchr(av, '/'))
	{
		*road = "./";
		*file = av;
	}
	else
	{
		*road = ft_strndup(av, ft_strrchr(av, '/') - av + 1);
		*file = ft_strdup(ft_strrchr(av, '/') + 1);
	}
}

void		full_tmp(t_path **tmp, char *av, char *road, char *file)
{
	*tmp = (t_path *)malloc(sizeof(t_path));
	(*tmp)->av = av;
	(*tmp)->road = road;
	(*tmp)->type = 'd';
	(*tmp)->file = file;
	(*tmp)->next = NULL;
}

int			check_right_path(char *av, t_dir *inform, t_path **tmp, t_key *key)
{
	char	*road;
	char	*file;

	create_2_args(av, &road, &file);
	inform->dir = opendir(road);
	if (!inform->dir)
		return (0);
	else
		while (file && *file && (inform->entry = readdir(inform->dir)))
			if (!ft_strcmp(inform->entry->d_name, file))
			{
				full_tmp(tmp, av, road, file);
				lstat(av, &(*tmp)->buff);
				key->count++;
				if (key->key_time || key->key_list)
					ft_find_time(&((*tmp)->time), (*tmp)->buff);
				!S_ISDIR((*tmp)->buff.st_mode) ? key->file = 1 : 0;
				!S_ISDIR((*tmp)->buff.st_mode) ? (*tmp)->type = 'f' : 0;
				break ;
			}
	(!file || !*file) ? full_tmp(tmp, av, road, file) : 0;
	(!file || !*file) ? key->count++ : 0;
	closedir(inform->dir);
	return (*tmp ? 1 : 0);
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

void		find_path(t_ls *ls, char **av)
{
	t_path	*tmp;

	ls->path = NULL;
	tmp = NULL;
	if (!*av)
	{
		full_tmp(&tmp, "./", "./", NULL);
		add_and_sort(ls->keys, &ls->path, tmp);
		ls->keys.count++;
	}
	while (*av)
	{
		tmp = NULL;
		if (check_right_path(*av, &ls->inform, &tmp, &ls->keys))
			add_and_sort(ls->keys, &ls->path, tmp);
		else
			ft_printf("ft_ls: %s: No such file or directory\n", *av);
		av++;
	}
}
