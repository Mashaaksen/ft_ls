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

void			ft_align_str_left(char *str, int align)
{
	write(1, str, ft_strlen(str));
	while (align-- > 0)
		write(1, " ", 1);
}

void			ft_align_str_right(char *str, int align)
{
	while (align-- > 0)
		write(1, " ", 1);
	write(1, str, ft_strlen(str));
}

void			ft_print_digit_align(unsigned long long value, int align)
{
	char		*str;

	str = ft_itoa_base(value, '\0');
	ft_align_str_right(str, align - ft_strlen(str));
	free(str);
}

void			ft_print_time(struct stat buf, t_keys keys)
{
	char        *temp;
	char		*curr_str;
	struct timespec			st_time;

	st_time = (keys.flags & mask_u) ? buf.st_atimespec : buf.st_mtimespec;
	curr_str = ctime(&st_time.tv_sec);
	temp = ft_strndup(ft_strchr(curr_str, ' '), (ft_strchr(curr_str, ':') - ft_strchr(curr_str, ' ') - 2));
	write(1, temp, ft_strlen(temp));
	free(temp);
	if (time(NULL) - st_time.tv_sec >= 15770000)
	{
		temp = ft_strndup(ft_strrchr(curr_str, ' '), (ft_strchr(curr_str, '\n') - ft_strrchr(curr_str, ' ')));
		ft_align_str_left(temp, 1);
	}
	else
	{
		temp = ft_strndup(ft_strchr(curr_str, ':') - 2, (ft_strrchr(curr_str, ' ') - ft_strchr(curr_str, ':') - 1));
		ft_align_str_left(temp, 1);
	}
	free(temp);
}

void			ft_print_target(char *target)
{
	write(1, " -> ", 4);
	write(1, target, ft_strlen(target));
}

void			ft_print_file(t_files *file, t_keys keys)
{
	char		*str;

	str = NULL;
	if (!(keys.flags & mask_l))
	{
		write(1, file->file, ft_strlen(file->file));
		write(1, "\n", 1);
	}
	else
	{
		ft_print_type(file);
		ft_align_str_left(file->permission, 0);
		ft_print_digit_align(file->buf.st_nlink, keys.length_link + 1);
		write(1, " ", 1);
		if (!(keys.flags & mask_g))
		{
			ft_align_str_left(file->pwd, keys.length_pwd - ft_strlen(file->pwd));
			write(1, "  ", 2);
		}
		ft_align_str_left(file->group, keys.length_group - ft_strlen(file->group));
		ft_print_digit_align((int)file->buf.st_size, keys.length_size + 2);
		ft_print_time(file->buf, keys);
		write(1, file->file, ft_strlen(file->file));
		if (file->target)
			ft_print_target(file->target);
		write(1, "\n", 1);
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
				write(1, "total ", 6);
				ft_print_digit_align(total, 0);
				write(1, "\n", 1);
				total = -1;
			}
			ft_print_file(files, keys);
		}
		files = files->next;
	}
}

void			ft_print_only_file(t_files *files, t_keys keys, int *first_time)
{
	while (files)
	{
		if (!S_ISDIR(files->buf.st_mode))
		{
			*first_time += 1;
			ft_print_file(files, keys);
		}
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
		ft_print_only_file(files, keys, &in_the_first_time);
	while (files)
	{
		if (S_ISDIR(files->buf.st_mode) && (*files->file != '.' || ((keys.flags & mask_a) &&
				((ft_strcmp(files->file, ".") && ft_strcmp(files->file, ".."))
				|| !ft_strcmp(files->full_path, files->file))) ||
				!ft_strcmp(files->full_path, files->file)))
		{
			total = -1;
			if (in_the_first_time++)
			{
				write(1, "\n", 1);
				write(1, files->full_path, ft_strlen(files->full_path));
				write(1, ":\n", 2);
			}
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
