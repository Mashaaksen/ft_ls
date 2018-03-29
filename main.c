/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:34:29 by maksenov          #+#    #+#             */
/*   Updated: 2018/03/23 18:34:30 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_print_type(t_files *file)
{
	if (S_ISBLK(file->buf.st_mode))
		write(1, "b", 1);
	else if (S_ISCHR(file->buf.st_mode))
		write(1, "c", 1);
	else if (S_ISDIR(file->buf.st_mode))
		write(1, "d", 1);
	else if (S_ISREG(file->buf.st_mode))
		write(1, "-", 1);
	else if (S_ISFIFO(file->buf.st_mode))
		write(1, "f", 1);
	else if (S_ISLNK(file->buf.st_mode))
		write(1, "l", 1);
	else if (S_ISSOCK(file->buf.st_mode))
		write(1, "s", 1);
	else
		write(1, "*", 1);
}

void			ft_print_time(struct stat buf)
{
	char        *temp;
	char		*curr_str;

	curr_str = ctime(&buf.st_mtimespec.tv_sec);
//	arr = ft_strsplit(curr_str, ' ');
	temp = ft_strndup(ft_strchr(curr_str, ' '), (ft_strchr(curr_str, ':') - ft_strchr(curr_str, ' ') - 2));
	write(1, " ", 1);
	write(1, temp, ft_strlen(temp));
	// printf(" %s", temp);
	free(temp);
	if (time(NULL) - buf.st_mtimespec.tv_sec >= 15770000 || time(NULL) - buf.st_mtimespec.tv_sec <= 3)
	{
		temp = ft_strndup(ft_strrchr(curr_str, ' '), (ft_strchr(curr_str, '\n') - ft_strrchr(curr_str, ' ')));
		write(1, temp, ft_strlen(temp));
		write(1, " ", 1);
		//printf("%s ", temp);
	}
	else
	{
		temp = ft_strndup(ft_strchr(curr_str, ':') - 2, (ft_strrchr(curr_str, ' ') - ft_strchr(curr_str, ':') - 1));
		write(1, temp, ft_strlen(temp));
		write(1, " ", 1);
		//printf("%s ", temp);
	}
	free(temp);
}

void			ft_print_file(t_files *file, t_keys keys)
{
	if (!(keys.flags & mask_l))
		printf("%s\n", file->file);
	else
	{
		ft_print_type(file);
		printf("%-*s %*d", keys.length_permission, file->permission, keys.length_link, file->buf.st_nlink);
		printf(" %-*s %-*s %*d ", keys.length_pwd, file->pwd,
	keys.length_group, file->group, keys.length_size, (int)file->buf.st_size);
		ft_print_time(file->buf); //из-за массива двумерного
		printf("%s", file->file);
		if (file->target)
			printf(" -> %s", file->target);
		printf("\n");
	}
}

void			ft_print_list(t_files *files, t_keys keys, int total)
{
	while (files)
	{
		if (*(files->file) != '.' || (keys.flags & mask_a) || (ft_strrchr(files->file, '/')
				&& *(ft_strrchr(files->file, '/') + 1) != '.'))
		{
			if (total != -1 && (keys.flags & mask_l))
			{
				printf("total %d\n", total);
				total = -1;
			}
			ft_print_file(files, keys);
		}
		files = files->next;
	}
}

void			ft_print_only_file(t_files *files, t_keys keys)
{
	while (files)
	{
		if (!S_ISDIR(files->buf.st_mode))
			ft_print_file(files, keys);
		files = files->next;
	}
}

void            ft_free_t_files(t_files **files)
{
	t_files     *head;

	head = (*files)->next;
	(*files)->full_path ? free((*files)->full_path) : 0;
	(*files)->group ? free((*files)->group) : 0;
	(*files)->pwd ? free((*files)->pwd) : 0;
	(*files)->file ? free((*files)->file) : 0;
	(*files)->target ? free((*files)->target) : 0;
	(*files)->permission ? free((*files)->permission) : 0;
	(*files)->next = NULL;
	free(*files);
	*files = head;
}

void			ft_start_ls(t_files *files, t_keys keys)
{
	t_files		*opens_folder;
	static int	in_the_first_time = 0;
	int			total;

	opens_folder = NULL;
	if (!in_the_first_time)
		ft_print_only_file(files, keys);
	while (files)
	{
		if (S_ISDIR(files->buf.st_mode) && (*files->file != '.' || ((keys.flags & mask_a) &&
				((ft_strcmp(files->file, ".") && ft_strcmp(files->file, ".."))
				|| !ft_strcmp(files->full_path, files->file))) ||
				!ft_strcmp(files->full_path, files->file)))
		{
			total = -1;
			if (in_the_first_time++)
				ft_printf("\n%s: \n", files->full_path);
			opens_folder = ft_opendir(files, &keys, &total);
			ft_print_list(opens_folder, keys, total);
			ft_initialize_length(&keys);
			if ((keys.flags & mask_R) && opens_folder)
				ft_start_ls(opens_folder, keys);
			else
			{
				while (opens_folder)
					ft_free_t_files(&opens_folder);
			}
		}
		ft_free_t_files(&files);
	}
}

int				main(int ac, char **av)
{
	t_ls		ls;

	ft_initialize_ls(&ls);
	ft_verification_param(ac, av, &ls);
	ft_start_ls(ls.files, ls.keys);
	return (0);
}
