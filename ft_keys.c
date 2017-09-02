/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:35:43 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:35:44 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				add_keys(t_key **key, char c)
{
	t_key			*tmp;
	t_key			*p;

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

int 				get_true_path(char *str, t_path **tmp, int new)
{
	t_dir			dir;
	char 			**way;
	int 			i;
	int 			flag;

	i = 0;
	flag = 0;
	way = ft_strsplit(str, '/');
	*tmp = (t_path *)malloc(sizeof(t_path));
	(*tmp)->next = NULL;
	(*tmp)->name_file = NULL;
	(*tmp)->road = (!new ? way[0] : str);
	if (!new)
	{
		while (way[i] && way[i + 1])
		{
			flag = 0;
			dir.dir = opendir((*tmp)->road);
			if (dir.dir == NULL)
				return (-1);
			while ((dir.entry = readdir(dir.dir)))
				if (!ft_strcmp(dir.entry->d_name, way[i + 1]))
				{
					flag++;
					lstat(ft_strjoin(ft_strjoin((*tmp)->road, "/"), way[i + 1]), &dir.buff);
					if (!S_ISDIR(dir.buff.st_mode))
						(*tmp)->name_file = way[i + 1];
					else
						(*tmp)->road = ft_strjoin(ft_strjoin((*tmp)->road, "/"), way[i + 1]);
					break;
				}
			closedir(dir.dir);
			if (flag == 0)
				return (-1);
			i++;
		}
		if (!way[1])
		{
			dir.dir = opendir(str);
			if (!dir.dir)
			{
				dir.dir = opendir("./");
				while ((dir.entry = readdir(dir.dir)))
					if (!ft_strcmp(dir.entry->d_name, way[0]))
					{
						flag++;
						lstat(ft_strjoin(ft_strjoin((*tmp)->road, "/"), way[0]), &dir.buff);
						if (!S_ISDIR(dir.buff.st_mode))
						{
							(*tmp)->name_file = way[0];
							(*tmp)->road = "./";
						}
						else
							(*tmp)->road = ft_strjoin(ft_strjoin((*tmp)->road, "/"), way[i + 1]);
						break;
					}
				closedir(dir.dir);
				return (flag ? 0 : -1);
			}
			(*tmp)->road = ft_strjoin((*tmp)->road, "/");
			closedir(dir.dir);
		}
	}
	return (0);
}

int 				add_path(char *str, t_path **path, int flag)
{
	t_path			*tmp;
	t_path			*head;

	if (ft_strcmp(str, "/") && get_true_path(str, &tmp, flag) == -1)
		return (-1);
	else if (!ft_strcmp(str, "/"))
		get_true_path(str, &tmp, 1);
	if (*path == NULL)
		*path = tmp;
	else
	{
		head = *path;
		while ((*path)->next != NULL)
			*path = (*path)->next;
		(*path)->next = tmp;
		*path = head;
	}
	return (0);
}

void				ft_keys(char **av, t_key **key, t_path **path, int *len)
{
	int				i;

	i = 1;
	*len = 0;
	while (av[i] != NULL && *av[i] == '-' && av[i][1] != '\0')
		check_keys(av[i++], key);
	while (av[i] != NULL)
	{
		if (add_path(av[i++], path, 0) == -1)
			ft_printf("ft_ls: %s: No such file or directory\n", av[i - 1]);
		(*len)++;
	}
	if (*path == NULL && *len == 0)
	{
		add_path(".", path, 1);
		(*len)++;
	}
}
