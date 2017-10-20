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

void 		new_tmp(t_path **p, char *road)
{
	(*p) = (t_path *)malloc(sizeof(t_path));
	(*p)->av = road;
	(*p)->road = road;
	(*p)->file = NULL;
	(*p)->next = NULL;
}

int			check_right_path(char *av, t_dir *inform, t_path **tmp, t_key key)
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
				create(tmp, &key, *inform, av);
				break ;
			}
	if (!file || !*file)
	{
		new_tmp(tmp, road);
		stat_create(&key, tmp);
		key.count++;
	}
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
	int	i;

	ls->path = NULL;
	tmp = NULL;
	if (!*av)
	{
		new_tmp(&tmp, "./");
		stat_create(&ls->keys, &tmp);
		i = (int)ft_strlen(tmp->av);
		i > ls->keys.max_len_name ? ls->keys.max_len_name = i : 0;
		if (tmp->type != 'd')
			ls->keys.file++;
		add_and_sort(ls->keys, &ls->path, tmp);
		ls->keys.count++;
	}
	while (*av)
	{
		tmp = NULL;
		if (check_right_path(*av, &ls->inform, &tmp, ls->keys))
		{
			i = (int)ft_strlen(tmp->av);
			i > ls->keys.max_len_name ? ls->keys.max_len_name = i : 0;
			if (tmp->type != 'd')
				ls->keys.file++;
			add_and_sort(ls->keys, &ls->path, tmp);
		}
		else
			ft_printf("ft_ls: %s: No such file or directory\n", *av);
		av++;
	}
}
