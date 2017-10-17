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

	inform.dir = opendir(path->file ? ft_strjoin(path->road,
ft_strjoin("/", path->file)) : path->road);
	if (!inform.dir)
		return (0);
	while ((inform.entry = readdir(inform.dir)))
	{
		full_tmp(&p, ft_strjoin(ft_strjoin(path->av, "/"),
inform.entry->d_name), path->av, ft_strdup(inform.entry->d_name));
		lstat(p->av, &p->buff);
		key->count++;
		(key->key_time || key->key_list) ? ft_find_time(&p->time, p->buff) : 0;
		S_ISDIR(p->buff.st_mode) ? p->type = 'd' : 0;
		!S_ISDIR(p->buff.st_mode) ? p->type = 'f' : 0;
		!S_ISDIR(p->buff.st_mode) ? key->file = 1 : 0;
		if ((key->key_all && *(p->file) == '.') || *(p->file) != '.')
			key->total += p->buff.st_blocks;
		add_and_sort(*key, tmp, p);
	}
	closedir(inform.dir);
	return (1);
}

void				add_list(t_path *path, t_key *keys,
t_char_list **list, t_char_list *tmp)
{
	t_char_list		*head;

	tmp = get_list(path, keys, 0, tmp);
	if (*(tmp->tipe) == 'l')
		add_terget(path, &tmp);
	if (!*list)
		*list = tmp;
	else
	{
		head = *list;
		while (*list && (*list)->next)
			*list = (*list)->next;
		(*list)->next = tmp;
		*list = head;
	}
}

t_char_list			*get_list(t_path *path, t_key *keys, int i,
t_char_list *tmp)
{
	tmp = (t_char_list *)malloc(sizeof(t_char_list));
	print_tipe(path->buff.st_mode, &tmp->tipe);
	print_mode(path->buff.st_mode, &tmp->mode);
	tmp->st_nlink = path->buff.st_nlink;
	tmp->pw_name = ft_strdup(path->uid->pw_name);
	tmp->gr_name = ft_strdup(path->gid->gr_name);
	tmp->st_size = path->buff.st_size;
	tmp->year = path->time.year;
	tmp->str_month = path->time.str_month;
	tmp->day = path->time.day;
	tmp->hour = path->time.hour;
	tmp->minute = path->time.minute;
	tmp->file = path->file;
	tmp->av = path->av;
	i = (int)ft_strlen(ft_itoa_base((size_t)tmp->st_size, 'i'));
	(i > keys->max_size) ? keys->max_size = i : 0;
	i = (int)ft_strlen(ft_itoa_base((size_t)tmp->st_nlink, 'i'));
	(i > keys->max_link) ? keys->max_link = i : 0;
	i = (int)ft_strlen(tmp->pw_name);
	(i > keys->max_name_pw) ? keys->max_name_pw = i : 0;
	i = (int)ft_strlen(tmp->gr_name);
	(i > keys->max_name_gr) ? keys->max_name_gr = i : 0;
	tmp->next = NULL;
	return (tmp);
}

void				print_all(t_path *path, t_key keys)
{
	t_char_list		*list;

	list = NULL;
	while (path != NULL)
	{
		if ((keys.key_all && *(path->file) == '.') || *(path->file) != '.')
		{
			!keys.key_list ? ft_printf("%s\n", path->file) : 0;
			(keys.key_list) ? path->uid = getpwuid(path->buff.st_uid) : 0;
			(keys.key_list) ? path->gid = getgrgid(path->buff.st_gid) : 0;
			(keys.key_list) ? add_list(path, &keys, &list, NULL) : 0;
		}
		path = path->next;
	}
	keys.key_list && list ? ft_printf("total %i\n", keys.total) : 0;
	while (list)
	{
		print_list(keys, list, 1);
		list = list->next;
	}
}

void				ft_ls(t_path *path, t_key keys, int flag, t_path *tmp)
{
	keys.file && !flag ? print_file(path, keys, NULL) : 0;
	while (path)
	{
		if (path->type == 'd' && (!path->file || (ft_strcmp(path->file, ".") && ft_strcmp(path->file, ".."))))
		{
			if (!path->file || ((keys.key_all || !flag) &&
*(path->file) == '.') || *(path->file) != '.')
			{
				keys.total = 0;
				keys.max_link = 0;
				keys.max_size = 0;
				keys.max_name_gr = 0;
				keys.max_name_pw = 0;
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
