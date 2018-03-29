/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opendir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:09:04 by maksenov          #+#    #+#             */
/*   Updated: 2018/03/23 18:09:05 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_files		*ft_opendir(t_files *files, t_keys *keys, int *total)
{
	t_files	*new_file;
	t_serv	serv;
	char	*path;
	char    *temp;
	int		errnum;

	new_file = NULL;
	serv.dir = opendir(files->full_path);
	!serv.dir ? perror(ft_strjoin("ft_ls: ", files->file)) : 0;
	if (serv.dir)
	{
		while ((serv.read = readdir(serv.dir)))
		{
			if (files->full_path[ft_strlen(files->full_path) - 1] != '/')
			{
				temp = ft_strjoin(files->full_path, "/");
				path = ft_strjoin(temp, serv.read->d_name);
				free(temp);
			}
			else
				path = ft_strjoin(files->full_path, serv.read->d_name);
			errnum = lstat(path, &serv.buf);
			errnum ? perror(ft_strjoin("ft_ls: ", serv.read->d_name)) : 0;
			if (!errnum)
			{
				*total == -1 ? *total = 0 : 0;
				if ((keys->flags & mask_l) && (*serv.read->d_name != '.' || (keys->flags & mask_a)))
					*total = *total + serv.buf.st_blocks;
				new_file = ft_initialize_files(new_file, serv.buf,
			serv.read->d_name, path, keys);
			}
			free(path);
		}
		closedir(serv.dir);
	}
	return (new_file);
}
