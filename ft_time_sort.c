/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_sort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:25:14 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:25:16 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_time(t_time a, t_time b)
{
	if (a.month > b.month)
		return (1);
	if (a.month == b.month)
	{
		if (a.day > b.day)
			return (1);
		if (a.day == b.day)
		{
			if (a.hour > b.hour)
				return (1);
			if (a.hour == b.hour)
			{
				if (a.minute > b.minute)
					return (1);
				if (a.minute == b.minute)
					if (a.sec > b.sec)
						return (1);
			}
		}
	}
	return (0);
}

int			check_sort_time(t_name *name)
{
	t_name	*tmp;

	tmp = name->next;
	while (tmp != NULL)
	{
		if (ft_time(tmp->time1, name->time1) == 1)
			return (0);
		name = name->next;
		tmp = tmp->next;
	}
	return (1);
}

void		initialization(t_name *name, t_name **tmp, t_name **p, t_name **r)
{
	(*r) = name;
	(*tmp) = name;
	(*p) = (*tmp)->next;
}

void		next_elem(t_name *r, int i, t_name **tmp, t_name **p)
{
	(*tmp)->next = (*p)->next;
	(*p)->next = (*tmp);
	(*tmp) = (i != 0 ? r->next : r);
	(*p) = (*tmp)->next;
}

void		ft_time_sort(t_name **name, int flag)
{
	t_name	*tmp;
	t_name	*p;
	t_name	*r;
	int		i;

	while (check_sort_time(*name) != 1)
	{
		i = 0;
		initialization(*name, &tmp, &p, &r);
		while (p != NULL)
		{
			if (ft_time(p->time1, tmp->time1) == 1)
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
