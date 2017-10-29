/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 19:25:17 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/15 19:25:18 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//void		create_2_args(char *av, char **road, char **file)
//{
//	*road = NULL;
//	*file = NULL;
//	if (!ft_strchr(av, '/'))
//	{
//		*road = "./";
//		*file = av;
//	}
//	else
//	{
//		*road = ft_strndup(av, ft_strrchr(av, '/') - av + 1);
//		*file = ft_strdup(ft_strrchr(av, '/') + 1);
//	}
//}
//
//void 		create_list_path(t_path **p, char *road)
//{
//	(*p) = (t_path *)malloc(sizeof(t_path));
//	(*p)->av = road;
//	(*p)->gid = NULL;
//	(*p)->uid = NULL;
//	(*p)->file = NULL;
//	(*p)->next = NULL;
//}
//
//int			check_right_path(char *av, t_dir *inform, t_path **tmp, t_key key)
//{
//	char	*road;
//	char	*file;
//
//	create_2_args(av, &road, &file);
//	inform->dir = opendir(road);
//	if (!inform->dir)
//		return (0);
//	else
//		while (file && *file && (inform->entry = readdir(inform->dir)))
//			if (!ft_strcmp(inform->entry->d_name, file))
//			{
//				create(tmp, &key, *inform, av);
//				break ;
//			}
//	if (!file || !*file)
//	{
//		//new_tmp(tmp, road);
//		stat_create(&key, tmp);
//		key.count++;
//	}
//	closedir(inform->dir);
//	return (*tmp ? 1 : 0);
//}
//
//int			alpha(char *a, char *b)
//{
//	char	*s1;
//	char	*s2;
//
//	s1 = a;
//	s2 = b;
//	while (*s1 || *s2)
//	{
//		if (*s1 != *s2)
//			return (*s1 > *s2 ? 1 : 0);
//		*s1 != '\0' ? s1++ : 0;
//		*s2 != '\0' ? s2++ : 0;
//	}
//	return (0);
//}

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
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	if (k > 0)
		*str = ft_strjoin(*str, "@");
	else if (acl != NULL)
		*str = ft_strjoin(*str, "+");
}

void 		create_path(struct stat buff, t_path **tmp, char *road, t_key **key)
{
	int				i;
	ssize_t			k;
	char 			link_name[PATH_LEN + 1];

	*tmp = (t_path *)malloc(sizeof(t_path));
	(*tmp)->file = ((ft_strrchr(road, '/') && (ft_strrchr(road, '/') + 1)) ? ft_strdup(ft_strrchr(road, '/') + 1) : NULL);
	(*tmp)->av = road;
	(*tmp)->buff = buff;
	(*tmp)->uid = NULL;
	(*tmp)->gid = NULL;
	print_tipe(buff.st_mode, &(*tmp)->type);
	if ((*key)->key_list)
	{
		print_mode(buff.st_mode, &(*tmp)->mode, road);
		(*tmp)->uid = getpwuid((*tmp)->buff.st_uid);
		(*tmp)->gid = getgrgid((*tmp)->buff.st_gid);
		i = (int)ft_strlen(ft_itoa_base((size_t)(*tmp)->buff.st_size, 'i'));
		(i > (*key)->max_size) ? (*key)->max_size = i : 0;
		i = (int)ft_strlen(ft_itoa_base((size_t)(*tmp)->buff.st_nlink, 'i'));
		(i > (*key)->max_link) ? (*key)->max_link = i : 0;
		i = (int)ft_strlen((*tmp)->mode);
		(i > (*key)->max_len_mode) ? (*key)->max_len_mode = i : 0;
		if ((*tmp)->uid && (*tmp)->gid)
		{
			i = (int) ft_strlen((*tmp)->uid->pw_name);
			(i > (*key)->max_name_pw) ? (*key)->max_name_pw = i : 0;
			i = (int) ft_strlen((*tmp)->gid->gr_name);
			(i > (*key)->max_name_gr) ? (*key)->max_name_gr = i : 0;

		}
		if ((*tmp)->type == 'l')
		{
			k = readlink((*tmp)->av, link_name, PATH_LEN);
			if (k >= PATH_LEN)
				(*tmp)->target = ft_strdup("Wrong: link filename too long!");
			else
			{
				if (k == -1)
					(*tmp)->target = ft_strdup("invalid symbolic link!");
				else
				{
					link_name[k] = '\0';
					(*tmp)->target = ft_strdup(link_name);
				}
			}
		}
	}
	(*tmp)->next = NULL;
}

void		find_path(t_ls *ls, char **av)
{
	t_path	*tmp;
	struct	stat buff;

	ls->path = NULL;
	tmp = NULL;
	if (!*av)
	{
		lstat("./", &buff);
		create_path(buff, &tmp, *av, &ls->keys);
		add_and_sort(ls->keys, &ls->path, tmp);
		ls->keys->count_all++;
	}
	while (*av)
	{
		lstat(*av, &buff);
		if (!buff.st_mode)
			ft_printf("ft_ls: %s: No such file or directory\n", *av);
		else
		{
			create_path(buff, &tmp, *av, &ls->keys);
			add_and_sort(ls->keys, &ls->path, tmp);
			tmp->type != 'd' ? ls->keys->file++ : 0;
			ls->keys->count_all++;
		}
		av++;
	}
//	if (!*av)
//	{
//		//new_tmp(&tmp, "./");
//		stat_create(&ls->keys, &tmp);
//		i = (int)ft_strlen(tmp->av);
//		i > ls->keys.max_len_name ? ls->keys.max_len_name = i : 0;
//		if (tmp->type != 'd')
//			ls->keys.file++;
//		add_and_sort(ls->keys, &ls->path, tmp);
//		ls->keys.count++;
//	}
//	while (*av)
//	{
//		tmp = NULL;
//		if (check_right_path(*av, &ls->inform, &tmp, ls->keys))
//		{
//			i = (int)ft_strlen(tmp->av);
//			i > ls->keys.max_len_name ? ls->keys.max_len_name = i : 0;
//			if (tmp->type != 'd')
//				ls->keys.file++;
//			add_and_sort(ls->keys, &ls->path, tmp);
//		}
//		else
//			ft_printf("ft_ls: %s: No such file or directory\n", *av);
//		av++;
//	}
}
