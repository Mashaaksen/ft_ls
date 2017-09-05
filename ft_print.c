/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:44:06 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:44:07 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		max_len_size(int *max, t_name *name, int flag)
{
	int		i;

	while (name != NULL)
	{
		i = (int)ft_strlen(ft_itoa_base((size_t)(flag == 1 ?
			name->size : name->link), 'i'));
		if (*max < i)
			*max = i;
		name = name->next;
	}
}

void		max_len_str(int *max, t_name *name, int flag)
{
	int		i;

	while (name != NULL)
	{
		i = (int)ft_strlen(flag == 1 ? name->name_gr : name->name_pw);
		if (*max < i)
			*max = i;
		name = name->next;
	}
}

void		ft_print_ls_1(t_ls *ls, t_name *tmp)
{
	ft_printf("%c%s %*i %-*s  %-*s  %*i %s %2i %02i:%02i %s", tmp->tipe,
	tmp->mode, ls->max_link, tmp->link, ls->max_name_pw, tmp->name_pw,
	ls->max_name_gr, tmp->name_gr, ls->max_size, (int)tmp->size, tmp->time,
	tmp->time1.day, tmp->time1.hour, tmp->time1.minute, tmp->str);
	if (ls->names->tipe == 'l')
		ft_printf(" -> %s\n", ls->names->target);
	else
		ft_printf("\n");
}

void		ft_print_ls(t_ls *ls, int l, t_key *key, int file)
{
	int		a;
	t_name	*tmp;

	max_len_str(&ls->max_name_gr, ls->names, 1);
	max_len_str(&ls->max_name_pw, ls->names, 2);
	max_len_size(&ls->max_size, ls->names, 1);
	max_len_size(&ls->max_link, ls->names, 2);
	a = (find_a(key) == 1 ? 1 : 0);
	while (ls->names != NULL)
	{
		tmp = ls->names;
		if ((*tmp->str == '.' && a == 1) || *tmp->str != '.')
		{
			if (file == 1 && l == 0)
				ft_printf("%s\n", ls->str);
			else if (l == 0)
				ft_printf("%s\n", tmp->str);
			else
				ft_print_ls_1(ls, tmp);
		}
		ls->names = ls->names->next;
	}
}
