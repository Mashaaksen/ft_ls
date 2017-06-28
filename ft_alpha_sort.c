/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alpha_sort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:56:56 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:56:57 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

int			check_sort(t_name *name)
{
	t_name	*tmp;

	if (name != NULL)
	{
		tmp = name->next;
		while (tmp != NULL)
		{
			if (alpha(name->str, tmp->str) == 1)
				return (0);
			name = name->next;
			tmp = tmp->next;
		}
	}
	return (1);
}

int			len_name(t_name *name)
{
	int		i;

	i = 0;
	while (name != NULL)
	{
		i++;
		name = name->next;
	}
	return (i);
}

void		add_tmp(t_name **name, t_name *p)
{
	t_name	*tmp;

	if (*name == NULL)
		*name = p;
	else
	{
		tmp = *name;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = p;
	}
}

void		ft_alpha_sort(t_name **name, int flag)
{
	t_name	*tmp;
	t_name	*p;
	t_name	*r;
	int		i;

	while (check_sort(*name) != 1)
	{
		i = 0;
		initialization(*name, &tmp, &p, &r);
		while (p != NULL)
		{
			if (alpha(tmp->str, p->str) == 1)
			{
				i != 0 ? r->next = p : 0;
				i == 0 ? r = p : 0;
				next_elem(r, i, &tmp, &p);
				i == 0 ? *name = r : 0;
			}
			if (i++ != 0)
				r = r->next;
			p = p->next;
			tmp = tmp->next;
		}
	}
	flag == 1 ? rostring(name) : 0;
}
