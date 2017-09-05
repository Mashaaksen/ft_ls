/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ordinary.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:25:42 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 16:25:47 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		create_tmp(t_path **tmp, char *str, t_name *name, int dot)
{
	while (name != NULL)
	{
		if (name->tipe == 'd' && ((!dot && *name->str != '.') || dot) && ft_strcmp(name->str, ".") && ft_strcmp(name->str, ".."))
			add_path(ft_strjoin(ft_strjoin(str, "/"), name->str), tmp, 1);
		name = name->next;
	}
}

int			only_dot(t_name *name)
{
	int		i;

	i = 0;
	while (name != NULL)
	{
		if (*(name->str) != '.')
			i++;
		name = name->next;
	}
	return (i == 0 ? 1 : 0);
}

int			ft_check(t_path *path, int rec, int len)
{
	int		flag;

	flag = 0;
	if (path != NULL)
	{
		flag = (path->next == NULL && rec == 0) ? 0 : 1;
		flag == 0 && len > 1 ? flag = 1 : 0;
	}
	return (flag);
}

void		fill_tab(t_key *key, t_ls **ls)
{
	(*ls)->rev = (find_r(key) == 1 ? 1 : 0);
	(*ls)->dot = find_a(key);
	(*ls)->total = 0;
}

void		ordinary(t_key *key, t_path *path, int len, int rec)
{
	t_ls	*ls;
	t_path	*tmp;

	tmp = NULL;
	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->names = NULL;
	fill_tab(key, &ls);
	ls->inscr = ft_check(path, rec, len);
	while (path != NULL && (tmp = NULL) == NULL)
	{
		if (ls->inscr == 1 && !path->name_file)
			ft_printf("\n%s:\n", path->all_name);
		ls->total = 0;
		if (!open_read_dir(&ls, path))
		{
			!find_time(key) ? ft_alpha_sort(&ls->names, ls->rev) :
			ft_time_sort(&ls->names, ls->rev);
			rec == 1 && !path->name_file ? create_tmp(&tmp, path->road, ls->names, ls->dot) : 0;
			(find_l(key) == 1 && !path->name_file) ?
			ft_printf("total %i\n", ls->total) : 0;
			ft_print_ls(ls, find_l(key) == 1 ? 1 : 0, key, path->name_file ? 1 : 0);
			(rec == 1 && tmp != NULL) ? ordinary(key, tmp, 0, rec) : 0;
		}
		path = path->next;
	}
}
