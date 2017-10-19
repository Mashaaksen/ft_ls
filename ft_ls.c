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

int					read_all(t_path *path, t_path **tmp, t_key *key)
{
	t_dir			inform;
	t_path			*p;
	int 			i;
	ssize_t			k;
	char 			link_name[PATH_LEN + 1];

	inform.dir = opendir(path->file ? ft_strjoin(path->road,
ft_strjoin("/", path->file)) : path->road);
	if (!inform.dir)
		return (0);
	while ((inform.entry = readdir(inform.dir)))
	{
		full_tmp(&p, ft_strjoin(ft_strjoin(path->av, "/"),
inform.entry->d_name), path->av, ft_strdup(inform.entry->d_name));
		lstat(p->av, &p->buff);
		print_tipe(p->buff.st_mode, &p->type);
		p->gid = NULL;
		p->uid = NULL;
		if (key->key_list && ((key->key_all && *(p->file) == '.') || *(p->file) != '.'))
		{
			print_tipe(p->buff.st_mode, &p->type);
			print_mode(p->buff.st_mode, &p->mode, p->av);
			p->uid = getpwuid(p->buff.st_uid);
			p->gid = getgrgid(p->buff.st_gid);
			i = (int)ft_strlen(ft_itoa_base((size_t)p->buff.st_size, 'i'));
			(i > key->max_size) ? key->max_size = i : 0;
			i = (int)ft_strlen(ft_itoa_base((size_t)p->buff.st_nlink, 'i'));
			(i > key->max_link) ? key->max_link = i : 0;
			i = (int)ft_strlen(p->mode);
			(i > key->max_len_mode) ? key->max_len_mode = i : 0;
			if (p->uid && p->gid)
			{
				i = (int) ft_strlen(p->uid->pw_name);
				(i > key->max_name_pw) ? key->max_name_pw = i : 0;
				i = (int) ft_strlen(p->gid->gr_name);
				(i > key->max_name_gr) ? key->max_name_gr = i : 0;

			}
			if (p->type == 'l')
			{
				k = readlink(p->av, link_name, PATH_LEN);
				if (k >= PATH_LEN)
					p->target = ft_strdup("Wrong: link filename too long!");
				else
				{
					if (k == -1)
						p->target = ft_strdup("invalid symbolic link!");
					else
					{
						link_name[k] = '\0';
						p->target = ft_strdup(link_name);
					}
				}
			}
		}
		key->count++;
		key->count_all++;
		*inform.entry->d_name != '.' ? key->count_without_dot++ : 0;
		i = (int) ft_strlen(p->file);
		if (*inform.entry->d_name != '.')
			(i > key->max_len_name) ? key->max_len_name = i : 0;
		else
			(i > key->max_len_name_dot) ? key->max_len_name_dot = i : 0;
		(key->key_time || key->key_list) ? ft_find_time(&p->time, p->buff, *key) : 0;
		if ((key->key_all && *(p->file) == '.') || *(p->file) != '.')
			key->total += p->buff.st_blocks;
		add_and_sort(*key, tmp, p);
	}
	closedir(inform.dir);
	return (1);
}

void		print_list(t_key keys, t_path *path, int dir)
{
	while (path)
	{
		if (((keys.key_all && *(path->file) == '.') || *(path->file) != '.'))
		{
			if (!keys.key_group)
				ft_printf("%c%-*s %*i %-*s  %-*s  %*i %s %2i", path->type, keys.max_len_mode,
					  path->mode, keys.max_link + 1, path->buff.st_nlink, keys.max_name_pw, path->uid->pw_name,
					  keys.max_name_gr, path->gid->gr_name, keys.max_size, (int) path->buff.st_size,
					  path->time.str_month, path->time.day);
			else
				ft_printf("%c%-*s %*i  %-*s  %*i %s %2i", path->type, keys.max_len_mode,
						  path->mode, keys.max_link + 1, path->buff.st_nlink,
						  keys.max_name_gr, path->gid->gr_name, keys.max_size, (int) path->buff.st_size,
						  path->time.str_month, path->time.day);
			if (path->time.year == 0 || path->time.month_now)
				ft_printf(" %02i:%02i %s", path->time.hour, path->time.minute, (!dir ? path->av : path->file));
			else
				ft_printf(" %5i %s", path->time.year, (!dir ? path->av : path->file));
			if (path->type == 'l')
				ft_printf(" -> %s\n", path->target);
			else
				ft_printf("\n");
		}
		path = path->next;
	}
}

void 				print_raw(t_path *path, int n, t_key key)
{
	int 			i;
	int 			len_name;

	if (key.key_all)
		len_name = (key.max_len_name_dot >= key.max_len_name ? key.max_len_name_dot : key.max_len_name);
	else
		len_name = key.max_len_name;
	i = 1;
	while (path && key.print_col >= 0)
	{
		while (path && !key.key_all && *(path->file) == '.')
			path = path->next;
		if (!path)
			break ;
		if (i == n - key.print_line)
		{
			ft_printf("%-*s", len_name + 4, path->file);
			key.print_col--;
		}
		i++;
		path = path->next;
		if (i == n + 1)
			i = 1;
	}
}

void 				print_col(t_key keys, t_path *path)
{
	int 			n;
	int 			len_name;
	int 			count;

	if (keys.key_all)
	{
		len_name = (keys.max_len_name_dot >= keys.max_len_name ? keys.max_len_name_dot : keys.max_len_name);
		count = keys.count_all;
	}
	else
	{
		len_name = keys.max_len_name;
		count = keys.count_without_dot;
	}
	keys.print_col = ((*keys.ws_col) - ((*keys.ws_col) / 10)) / (len_name + 8);
	keys.print_line = count / keys.print_col;
	n = keys.print_line;
	while (keys.print_line-- >= 0)
	{
		if (n != (keys.print_line + 1))
			ft_printf("\n");
		print_raw(path, n, keys);
	}
}

void				print_all(t_path *path, t_key keys)
{
	t_path			*tmp;

	tmp = path;
	if (!keys.key_list && keys.key_one)
	{
		while (path != NULL)
		{
			if ((keys.key_all && *(path->file) == '.') || *(path->file) != '.')
				ft_printf("%s\n", path->file);
			path = path->next;
		}

	}
	else if (!keys.key_one && !keys.key_list)
		print_col(keys, tmp);
	else
	{
		tmp ? ft_printf("total %i\n", keys.total) : 0;
		print_list(keys, tmp, 1);
	}
}

void				ft_ls(t_path *path, t_key keys, int flag, t_path *tmp)
{
	keys.file && !flag ? print_file(path, keys) : 0;
	while (path)
	{
		if (path->type == 'd' && (!path->file || (ft_strcmp(path->file, ".") && ft_strcmp(path->file, ".."))))
		{
			if (!path->file || ((keys.key_all || !flag) &&
*(path->file) == '.') || *(path->file) != '.')
			{
				keys.total = 0;
				keys.count_all = 0;
				keys.count_without_dot = 0;
				keys.max_link = 0;
				keys.max_size = 0;
				keys.max_name_gr = 0;
				keys.max_name_pw = 0;
				keys.max_name_pw = 0;
				keys.max_len_mode = 0;
				keys.max_len_name = 0;
				keys.max_len_name_dot = 0;
				(flag || keys.count > 1) ? ft_printf("\n%s:\n", path->av) : 0;
				if (read_all(path, &tmp, &keys))
				{
					print_all(tmp, keys);
					keys.key_recurs ? ft_ls(tmp, keys, flag + 1, NULL) : 0;
				}
				tmp = NULL;
			}
		}
		path = path->next;
	}
}
