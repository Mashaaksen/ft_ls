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

void		create_tmp(t_path **tmp, char *str, t_name *name)
{
	while (name != NULL)
	{
		if (name->tipe == 'd' && *(name->str) != '.')
			add_path(ft_strjoin(str, name->str), tmp);
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

	if (path != NULL)
	{
		flag = (path->next == NULL && rec == 0) ? 0 : 1;
		flag == 0 && len > 1 ? flag = 1 : 0;
	}
	else
		flag = 0;
	return (flag);
}

void		fill_tab(t_key *key, int *tab)
{
	tab[0] = (find_r(key) == 1 ? 1 : 0);
	tab[1] = find_a(key);
	tab[2] = 0;
}

void		ordinary(t_key *key, t_path *path, int len, int rec)
{
	char	*str;
	t_ls	*ls;
	t_path	*tmp;
	int		tab[4];

	ls = (t_ls *)malloc(sizeof(t_ls));
	ls->names = NULL;
	fill_tab(key, tab);
	tab[3] = ft_check(path, rec, len);
	while (path != NULL && (tmp = NULL) == NULL)
	{
		if (tab[3] == 1 && ft_strcmp(path->str, "."))
			ft_printf("\n%s:\n", path->str);
		str = ft_strjoin(path->str, "/");
		open_read_dir(str, ls, tab, path->file);
		!find_time(key) ? ft_alpha_sort(&ls->names, tab[0]) :
		ft_time_sort(&ls->names, tab[0]);
		rec == 1 ? create_tmp(&tmp, str, ls->names) : 0;
		(find_l(key) == 1 && only_dot(ls->names) == 0) ?
		ft_printf("total %i\n", tab[2]) : 0;
		ft_print_ls(ls, find_l(key) == 1 ? 1 : 0, key);
		(rec == 1 && tmp != NULL) ? ordinary(key, tmp, 0, rec) : 0;
		path = path->next;
	}
}
