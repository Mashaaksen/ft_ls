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

int			open_read_dir(t_ls **ls, t_path *path)
{
	(*ls)->dir.dir = opendir(path->road);
	if (!(*ls)->dir.dir)
		return (1);
	while (((*ls)->dir.entry = readdir((*ls)->dir.dir)))
	{
		if (path->name_file && ft_strcmp((*ls)->dir.entry->d_name, path->name_file))
			continue ;
		else if (path->name_file) {
			if (!lstat(ft_strjoin(ft_strjoin(path->road, "/"), (*ls)->dir.entry->d_name), &(*ls)->buff)) {
				(*ls)->str = ft_strjoin(ft_strjoin(path->road, "/"), (*ls)->dir.entry->d_name);
				ft_name(&(*ls)->names, ls);
				break;
			}
		}
		else if (!path->name_file)
		{
			if (!lstat(ft_strjoin(ft_strjoin(path->road, "/"), (*ls)->dir.entry->d_name), &(*ls)->buff))
				{
					(*ls)->str = ft_strjoin(ft_strjoin(path->road, "/"), (*ls)->dir.entry->d_name);
					ft_name(&(*ls)->names, ls);
					if (*((*ls)->dir.entry->d_name) != '.' || (*ls)->dot == 1)
						(*ls)->total += (*ls)->buff.st_blocks;
				}
		}
	}
	closedir((*ls)->dir.dir);
	return (0);
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
