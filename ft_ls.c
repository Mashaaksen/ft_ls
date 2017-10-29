/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 20:25:06 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/15 20:25:07 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

//void	create(t_path **tmp, t_key *key, t_dir inform, char *road)
//{
//	t_path			*p;
//	int 			i;
//
//	p = (t_path *)malloc(sizeof(t_path));
//	p->av = ft_strdup(ft_strjoin(ft_strjoin(road, "/"), inform.entry->d_name));
//	p->road = road;
//	p->file = ft_strdup(inform.entry->d_name);
//	p->next = NULL;
//	stat_create(key, &p);
//	key->count++;
//	key->count_all++;
//	*(p->file) != '.' ? key->count_without_dot++ : 0;
//	add_and_sort(*key, tmp, p);
//}
//
//
int					read_all(t_path *path, t_path **tmp, t_key **key)
{
	t_dir			inform;
	struct stat		buff;
	char 			*road;
	t_path			*p;

	inform.dir = opendir(path->av);
	if (!inform.dir)
		return (0);
	while ((inform.entry = readdir(inform.dir)))
	{
		p = NULL;
		road = ft_strjoin(path->av, inform.entry->d_name);
		lstat(road, &buff);
		create_path(buff, &p, road, key);
		add_and_sort(*key, tmp, p);
		if (((*key)->key_all && *(p->file) == '.') || *(p->file) != '.')
			(*key)->total += p->buff.st_blocks;
		(*key)->count_all++;
	}
	closedir(inform.dir);
	return (1);
}

void		ft_find_time(struct stat buff, t_key *key)
{
	char	*str_time;
	char 	*now_time;
	char	*str;
	time_t timer;

	if (key->file)
		str = NULL;
	timer = time(NULL);
	str_time = ft_strdup(/*key.key_use_atime ? ctime(&buff.st_atimespec.tv_sec) : */ctime(&buff.st_mtimespec.tv_sec));
	now_time = ctime(&timer);
	str = ft_strchr(str_time, ' ') + 1;
	ft_printf(" %.3s %2i", str, ft_atoi(ft_strchr(str, ' ')));
	if (ft_atoi(ft_strrchr(str_time, ' ')) != ft_atoi(ft_strrchr(now_time, ' ')))
		ft_printf(" %5i", ft_atoi(ft_strrchr(str_time, ' ')));
	else
	{
		str = ft_strchr((ft_strchr(str, ' ') + 1), ' ') + 1;
		ft_printf(" %02i:%02i", ft_atoi(str), ft_atoi((ft_strchr(str, ':') + 1)));
	}
//	tmp->year = ft_atoi(ft_strrchr(str_time, ' '));
//	if (key.key_use_atime && !ft_strncmp((ft_strchr(now_time, ' ') + 1), (ft_strchr(str_time, ' ') + 1), 3) && tmp->year == ft_atoi(ft_strrchr(now_time, ' ')))
//		tmp->month_now = 1;
//	if (!key.key_use_atime && tmp->year == ft_atoi(ft_strrchr(now_time, ' ')))
//		tmp->year = 0;
//	tmp->str_month = ft_strndup(ft_strchr(str_time, ' ') + 1, 3);
//	tmp->day = ft_atoi(ft_strchr(ft_strchr(str_time, ' ') + 1, ' '));
//	tmp->hour = ft_atoi(ft_strchr(str_time, ':') - 2);
}

void		print_list(t_key *keys, t_path *path, int dir)
{
	while (path)
	{
		if ((((keys->key_all && *(path->file) == '.') || *(path->file) != '.')) && ((!dir && path->type != 'd') || dir))
		{
//			if (!keys.key_group)
				ft_printf("%c%-*s %*i %-*s  %-*s  %*i", path->type, keys->max_len_mode,/* %s %2i*/
					  path->mode, keys->max_link + 1, path->buff.st_nlink, keys->max_name_pw, path->uid->pw_name,
						  keys->max_name_gr, path->gid->gr_name, keys->max_size, (int) path->buff.st_size/*,
					  path->time.str_month, path->time.day*/);
//			else
//				ft_printf("%c%-*s %*i  %-*s  %*i %s %2i", path->type, keys.max_len_mode,
//						  path->mode, keys.max_link + 1, path->buff.st_nlink,
//						  keys.max_name_gr, path->gid->gr_name, keys.max_size, (int) path->buff.st_size,
//						  path->time.str_month, path->time.day);
			ft_find_time(path->buff, keys);
			ft_printf(" %s", (!dir ? path->av : path->file));
			if (path->type == 'l')
				ft_printf(" -> %s\n", path->target);
			else
				ft_printf("\n");
		}
		path = path->next;
	}
}
//
//void 				print_raw(t_path *path, int n, t_key key, int dir)
//{
//	int 			i;
//	int 			len_name;
//
//	if (key.key_all)
//		len_name = (key.max_len_name_dot >= key.max_len_name ? key.max_len_name_dot : key.max_len_name);
//	else
//		len_name = key.max_len_name;
//	i = 1;
//	while (path && key.print_col >= 0)
//	{
//		while (path && ((!key.key_all && *(path->file) == '.') || (!dir && path->type == 'd')))
//			path = path->next;
//		if (!path)
//			break ;
//		if (i == n - key.print_line)
//		{
//			ft_printf("%-*s", len_name + 4, (dir ? path->file : path->road));
//			key.print_col--;
//		}
//		i++;
//		path = path->next;
//		if (i == n + 1)
//			i = 1;
//	}
//}
//
//void 				print_col(t_key keys, t_path *path, int dir)
//{
//	int 			n;
//	int 			len_name;
//	int 			count;
//
//	if (keys.key_all)
//	{
//		len_name = (keys.max_len_name_dot >= keys.max_len_name ? keys.max_len_name_dot : keys.max_len_name);
//		if (dir)
//			count = keys.count_all;
//		else
//			count = keys.file;
//	}
//	else
//	{
//		len_name = keys.max_len_name;
//		count = dir ? keys.count_without_dot : keys.file;
//	}
//	keys.print_col = (((*keys.ws_col) - 2) / (len_name + 10)) - 1;
//	keys.print_line = count / keys.print_col;
//	n = keys.print_line;
//	while (keys.print_line-- >= 0)
//	{
//		if (n != (keys.print_line + 1))
//			ft_printf("\n");
//		print_raw(path, n, keys, dir);
//	}
//}
//
void				print_all(t_path *path, t_key *keys, int dir)
{
	t_path			*tmp;

	tmp = path;
	if (!keys->key_list )//&& keys.key_one)
	{
		while (path != NULL)
		{
			if (((!dir && path->type != 'd') || dir) && ((keys->key_all && *(path->file) == '.') || *(path->file) != '.'))
				ft_printf("%s\n", !dir ? path->av : path->file);
			path = path->next;
		}

	}
//	else if (!keys.key_one && !keys.key_list)
//		print_col(keys, tmp, dir);
	else
	{
		tmp && dir ? ft_printf("total %i\n", keys->total) : 0;
		print_list(keys, tmp, dir);
	}
}

void				ft_ls(t_path *path, t_key *keys, t_path *tmp)
{
	keys->file ? print_all(path, keys, 0) : 0;
	keys->file ? keys->file = 0 : 0;
	while (path)
	{
		if (path->type == 'd' && (!path->file || (ft_strcmp(path->file, ".") && ft_strcmp(path->file, ".."))))
		{
			if (!path->file || ((keys->key_all) &&
*(path->file) == '.') || *(path->file) != '.')
			{
				keys->total = 0;
//				keys.count_without_dot = 0;
				keys->max_link = 0;
				keys->max_size = 0;
				keys->max_name_gr = 0;
				keys->max_name_pw = 0;
				keys->max_len_mode = 0;
//				keys.max_len_name = 0;
//				keys.max_len_name_dot = 0;
				(keys->count_all > 1) ? ft_printf("\n%s:\n", path->av) : 0;
				keys->count_all = 0;
				if (read_all(path, &tmp, &keys))
				{
					print_all(tmp, keys, 1);
					keys->key_recurs ? ft_ls(tmp, keys, NULL) : 0;
				}
				tmp = NULL;
			}
		}
		path = path->next;
	}
}
