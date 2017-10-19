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

void		print_tipe(mode_t mode, char *str)
{
	if (S_ISBLK(mode))
		*str = 'b';
	else if (S_ISCHR(mode))
		*str = 'c';
	else if (S_ISDIR(mode))
		*str = 'd';
	else if (S_ISREG(mode))
		*str = '-';
	else if (S_ISFIFO(mode))
		*str = 'f';
	else if (S_ISLNK(mode))
		*str = 'l';
	else if (S_ISSOCK(mode))
		*str = 's';
	else
		*str = '*';
}

void		print_mode(mode_t mode, char **str, char *path)
{
	ssize_t k;
	char 	*line;
	acl_t acl = NULL;
	acl_entry_t dummy;

	k = 0;
	line = NULL;
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
	k = listxattr(path, line, 0, XATTR_NOFOLLOW);
	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1) {
		acl_free(acl);
		acl = NULL;
	}
	if (k > 0)
		*str = ft_strjoin(*str, "@");
	else if (acl != NULL)
		*str = ft_strjoin(*str, "+");

}

void		print_file(t_path *path, t_key keys)
{
	if (!keys.key_list)
	{
		while (path != NULL)
		{
			if (path->type != 'd')
				if ((keys.key_all && *(path->file) == '.') || *(path->file) != '.')
					ft_printf("%s\n", path->file);
			path = path->next;
		}
	}
	else
		print_list(keys, path, 0);
}
