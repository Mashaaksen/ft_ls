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

int			ft_time(struct stat a, struct stat b, char *path, char *tmp)
{
	if (a.st_atimespec.tv_sec > b.st_atimespec.tv_sec)
		return (1);
	if (a.st_atimespec.tv_sec == b.st_atimespec.tv_sec)
	{
		if (a.st_atimespec.tv_nsec > b.st_atimespec.tv_nsec)
			return (1);
		if (a.st_atimespec.tv_nsec == b.st_atimespec.tv_nsec)
			return (!alpha(path, tmp) ? 1 : 0);
	}
	return (0);
}

void	forward_alpha(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && !alpha((*path)->next->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void	back_alpha(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && alpha((*path)->next->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		forward_time(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && ft_time((*path)->next->buff, tmp->buff, (*path)->next->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		back_time(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && !ft_time((*path)->next->buff, tmp->buff, (*path)->next->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		time_sort(t_key *keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	head = NULL;
	if (keys->key_rev == 0)
	{
		if (ft_time(tmp->buff, (*path)->buff, (*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			forward_time(path, tmp, head);
	}
	else
	{
		if (!ft_time(tmp->buff, (*path)->buff, (*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			back_time(path, tmp, head);
	}
}

void		alpha_sort(t_key *keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	head = NULL;
	if (keys->key_rev == 0)
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

void		add_and_sort(t_key *keys, t_path **path, t_path *tmp)
{
//	t_path	*head;

	if (*path == NULL)
		*path = tmp;
//	else if (keys.key_without_sort)
//	{
//		head = *path;
//		while ((*path)->next)
//			*path = (*path)->next;
//		(*path)->next = tmp;
//		*path = head;
//	}
	else
	{
		if (keys->key_time == 0)
			alpha_sort(keys, path, tmp);
		else
			time_sort(keys, path, tmp);
	}
}
