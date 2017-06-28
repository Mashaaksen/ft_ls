/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:26:35 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:26:36 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int			find_recursion(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 'R')
			return (1);
		key = key->next;
	}
	return (0);
}

void		open_read_dir(char *str, t_ls *ls, int *tab, char *file)
{
	ls->dir = opendir(str);
	if (file == NULL)
		while ((ls->entry = readdir(ls->dir)) != NULL)
		{
			if (lstat(ft_strjoin(str, ls->entry->d_name), &ls->buff) == 0)
			{
				ls->str = ft_strjoin(str, ls->entry->d_name);
				ft_name(&ls->names, ls);
				if (*(ls->entry->d_name) != '.' || tab[1] == 1)
					tab[2] += ls->buff.st_blocks;
			}
		}
	else
	{
		while ((ls->entry = readdir(ls->dir)) != NULL)
			if (!ft_strcmp(ls->entry->d_name, file))
			{
				if (lstat(ft_strjoin(str, ls->entry->d_name), &ls->buff) == 0)
				{
					ls->str = ft_strjoin(str, ls->entry->d_name);
					ft_name(&ls->names, ls);
					if (*(ls->entry->d_name) != '.' || tab[1] == 1)
						tab[2] += ls->buff.st_blocks;
				}
				break ;
			}
	}
	closedir(ls->dir);
}

int			main(int ac, char **av)
{
	t_key	*key;
	t_path	*path;
	int		len;

	ac = 0;
	key = NULL;
	path = NULL;
	ft_keys(av, &key, &path, &len);
	ordinary(key, path, len, find_recursion(key) == 1 ? 1 : 0);
	return (0);
}
