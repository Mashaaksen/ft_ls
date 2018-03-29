/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_insert_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:21:51 by maksenov          #+#    #+#             */
/*   Updated: 2018/03/23 18:21:52 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int					ft_alpha_comp(t_files *curr_file, t_files *new_file)
{
	if (ft_strcmp(curr_file->file, new_file->file) < 0)
		return (1);
	return (0);
}

int					ft_time_comp(t_files *curr_file, t_files *new_file)
{
	if (curr_file->buf.st_mtimespec.tv_sec > new_file->buf.st_mtimespec.tv_sec)
		return (1);
	if (curr_file->buf.st_mtimespec.tv_sec == new_file->buf.st_mtimespec.tv_sec)
	{
		if (curr_file->buf.st_mtimespec.tv_nsec >
				new_file->buf.st_mtimespec.tv_nsec)
			return (1);
		if (curr_file->buf.st_mtimespec.tv_nsec ==
				new_file->buf.st_mtimespec.tv_nsec)
			return (ft_alpha_comp(curr_file, new_file) ? 1 : 0);
	}
	return (0);
}

t_files				*ft_insert_files(t_files *files, t_files *new_files,
					t_keys keys)
{
	t_files			*head;
	int				vect_sort;
	ft_compare_type	compare_elem;

	vect_sort = (keys.flags & mask_r) ? 0 : 1;
	compare_elem = (keys.flags & mask_t) ? ft_time_comp : ft_alpha_comp;
	head = files;
	if (!files || (files && compare_elem(files, new_files) != vect_sort))
	{
		if (files)
			new_files->next = files;
		return (new_files);
	}
	else
	{
		while (files)
		{
			if (!files->next || (compare_elem(files, new_files) == vect_sort &&
					compare_elem(files->next, new_files) != vect_sort))
			{
				new_files->next = files->next;
				files->next = new_files;
				break ;
			}
			files = files->next;
		}
	}
	return (head);
}
