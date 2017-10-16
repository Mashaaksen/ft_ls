/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 13:22:52 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/16 13:22:54 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		print_tipe(mode_t mode, char **str)
{
	*str = NULL;
	if (S_ISBLK(mode))
		*str = "b";
	else if (S_ISCHR(mode))
		*str = "c";
	else if (S_ISDIR(mode))
		*str = "d";
	else if (S_ISREG(mode))
		*str = "-";
	else if (S_ISFIFO(mode))
		*str = "f";
	else if (S_ISLNK(mode))
		*str = "l";
	else if (S_ISSOCK(mode))
		*str = "s";
	else
		*str = "*";
}

void		print_mode(mode_t mode, char **str)
{
	*str = "";
	*str = ft_strjoin(*str, ((mode & S_IRUSR) ? "r" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IWUSR) ? "w" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IXUSR) ? "x" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IRGRP) ? "r" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IWGRP) ? "w" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IXGRP) ? "x" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IROTH) ? "r" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IWOTH) ? "w" : "-"));
	if (mode & S_ISVTX)
		*str = ft_strjoin(*str, "t");
	else if (mode & S_IXOTH)
		*str = ft_strjoin(*str, "x");
	else
		*str = ft_strjoin(*str, "-");
}

void		print_list(t_key keys, t_char_list *list, int dir)
{
	ft_printf("%s%s %*i %-*s  %-*s  %*i %s %2i", list->tipe,
list->mode, keys.max_link + 1, list->st_nlink, keys.max_name_pw, list->pw_name,
keys.max_name_gr, list->gr_name, keys.max_size, (int)list->st_size,
list->str_month, list->day);
	if (list->year == 0)
		ft_printf(" %02i:%02i %s", list->hour, list->minute, (!dir ? list->av : list->file));
	else
		ft_printf(" %i %s", list->year, (!dir ? list->av : list->file));
	if (*(list->tipe) == 'l')
		ft_printf(" -> %s\n", list->target);
	else
		ft_printf("\n");
}

void		print_file(t_path *path, t_key keys, t_char_list *list)
{
	while (path != NULL)
	{
		if (path->type == 'f')
		{
			if ((keys.key_all && *(path->file) == '.') || *(path->file) != '.')
			{
				if (!keys.key_list)
					ft_printf("%s\n", path->file);
				else
				{
					path->uid = getpwuid(path->buff.st_uid);
					path->gid = getgrgid(path->buff.st_gid);
					add_list(path, &keys, &list, NULL);
				}
			}
		}
		path = path->next;
	}
	while (list)
	{
		print_list(keys, list, 0);
		list = list->next;
	}
}
