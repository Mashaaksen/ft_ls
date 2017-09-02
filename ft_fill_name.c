/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_name.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 16:40:10 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 16:40:24 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			find_month(char *str, int i)
{
	if (i++ && !ft_strcmp(str, "Jan"))
		return (i);
	if (i++ && !ft_strcmp(str, "Feb"))
		return (i);
	if (i++ && !ft_strcmp(str, "Mar"))
		return (i);
	if (i++ && !ft_strcmp(str, "Apr"))
		return (i);
	if (i++ && !ft_strcmp(str, "May"))
		return (i);
	if (i++ && !ft_strcmp(str, "Jun"))
		return (i);
	if (i++ && !ft_strcmp(str, "Jul"))
		return (i);
	if (i++ && !ft_strcmp(str, "Aug"))
		return (i);
	if (i++ && !ft_strcmp(str, "Sep"))
		return (i);
	if (i++ && !ft_strcmp(str, "Oct"))
		return (i);
	if (i++ && !ft_strcmp(str, "Nov"))
		return (i);
	if (i++ && !ft_strcmp(str, "Dec"))
		return (i);
	return (i);
}

void		ft_find_time(t_name **p, t_ls *ls)
{
	char	**a;
	char	**b;

	(*p)->time = ctime(&ls->buff.st_mtimespec.tv_sec);
	a = ft_strsplit((*p)->time, ' ');
	(*p)->time1.month = find_month(a[1], 0);
	(*p)->time1.day = ft_atoi(a[2]);
	b = ft_strsplit(a[3], ':');
	(*p)->time = a[1];
	(*p)->time1.hour = ft_atoi(b[0]);
	(*p)->time1.minute = ft_atoi(b[1]);
	(*p)->time1.sec = ft_atoi(b[2]);
}

void		fill_p(t_ls *ls, t_name **p)
{
	(*p) = (t_name *)malloc(sizeof(t_name));
	(*p)->str = ft_strdup(ls->dir.entry->d_name);
	ls->uid = getpwuid(ls->buff.st_uid);
	ls->gid = getgrgid(ls->buff.st_gid);
	(*p)->name_pw = ft_strdup(ls->uid->pw_name);
	(*p)->name_gr = ft_strdup(ls->gid->gr_name);
	ft_find_time(p, ls);
	(*p)->size = ls->buff.st_size;
	(*p)->link = ls->buff.st_nlink;
	find_tipe(&(*p)->tipe, ls->buff.st_mode);
	find_mode(&(*p)->mode, ls->buff.st_mode);
}

void		print_ls_link(t_ls *ls, t_name *p, char *link_name, ssize_t k)
{
	if (p->tipe == 'l')
	{
		k = readlink(ls->str, link_name, PATH_LEN);
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

void		ft_name(t_name **names, t_ls **ls)
{
	t_name	*tmp;
	t_name	*p;
	char	link_name[PATH_LEN];

	fill_p(*ls, &p);
	print_ls_link(*ls, p, link_name, 0);
	p->next = NULL;
	if (*names == NULL)
		*names = p;
	else
	{
		tmp = *names;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = p;
	}
}
