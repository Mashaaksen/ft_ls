/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 13:06:54 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/16 13:06:55 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		forward_time(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && !ft_time(tmp->next->time, (*path)->time, (*path)->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		back_time(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && tmp->next && ft_time(tmp->next->time, (*path)->time, (*path)->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		time_sort(t_key keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	head = NULL;
	if (keys.key_rev == 0)
	{
		if (ft_time(tmp->time, (*path)->time, (*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			forward_time(path, tmp, head);
	}
	else
	{
		if (!ft_time(tmp->time, (*path)->time, (*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			back_time(path, tmp, head);
	}
}

void		alpha_sort(t_key keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	head = NULL;
	if (keys.key_rev == 0)
	{
		if (alpha((*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			forward_alpha(path, tmp, head);
	}
	else
	{
		if (!alpha((*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			back_alpha(path, tmp, head);
	}
}

void		add_and_sort(t_key keys, t_path **path, t_path *tmp)
{
	if (*path == NULL)
		*path = tmp;
	else
	{
		if (keys.key_time == 0)
			alpha_sort(keys, path, tmp);
		else
			time_sort(keys, path, tmp);
	}
}
