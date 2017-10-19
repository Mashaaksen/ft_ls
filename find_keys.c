/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/14 16:55:12 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/14 16:55:14 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

void	new_ls(t_ls **ls)
{
	(*ls)->keys.key_all = 0;
	(*ls)->keys.key_list = 0;
	(*ls)->keys.key_recurs = 0;
	(*ls)->keys.key_rev = 0;
	(*ls)->keys.key_time = 0;
	(*ls)->keys.count = 0;
	(*ls)->keys.file = 0;
	(*ls)->keys.key_one = 0;
	(*ls)->keys.key_group = 0;
	(*ls)->keys.key_without_sort = 0;
	(*ls)->keys.key_use_atime = 0;
}

void	find_keys(t_ls *ls, char ***av)
{
	new_ls(&ls);
	while (**av && (**av)[0] == '-' && (**av)[1])
	{
		(**av)++;
		while (***av)
		{
			if (***av != 'l' && ***av != 'R' && ***av != 'a' &&
***av != 'r' && ***av != 't' && ***av != '1' && ***av != 'g' && ***av != 'G' && ***av != 'u' && ***av != 'f')
			{
				ft_printf("ft_ls: illegal option -- %c\nusage:"
"ft_ls [-lraRtgGuf1] [file ...]\n", ***av);
				exit(0);
			}
			if (***av == 'l')
			{
				ls->keys.key_list = 1;
				ls->keys.key_one ? ls->keys.key_one = 0 : 0;
			}
			if (***av == 'g')
			{
				ls->keys.key_group = 1;
				!ls->keys.key_list ? ls->keys.key_list = 1 : 0;
			}
			***av == 'u' ? ls->keys.key_use_atime = 1 : 0;
			if (***av == 'f')
			{
				ls->keys.key_without_sort = 1;
				!ls->keys.key_all ? ls->keys.key_all = 1 : 0;
			}
			***av == 'G' ? ls->keys.key_color = 1 : 0;
			***av == 'r' ? ls->keys.key_rev = 1 : 0;
			***av == 'R' ? ls->keys.key_recurs = 1 : 0;
			***av == 'a' ? ls->keys.key_all = 1 : 0;
			***av == 't' ? ls->keys.key_time = 1 : 0;
			if (***av == '1')
			{
				ls->keys.key_one = 1;
				ls->keys.key_list ? ls->keys.key_list = 0 : 0;
			}
			(**av)++;
		}
		(*av)++;
	}
}
