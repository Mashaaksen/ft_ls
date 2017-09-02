/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:17:21 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:17:22 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		find_mode(char **str, mode_t mode)
{
	*str = ft_strdup("");
	*str = ft_strjoin(*str, (mode & S_IRUSR) ? "r" : "-");
	*str = ft_strjoin(*str, (mode & S_IWUSR) ? "w" : "-");
	*str = ft_strjoin(*str, (mode & S_IXUSR) ? "x" : "-");
	*str = ft_strjoin(*str, (mode & S_IRGRP) ? "r" : "-");
	*str = ft_strjoin(*str, (mode & S_IWGRP) ? "w" : "-");
	*str = ft_strjoin(*str, (mode & S_IXGRP) ? "x" : "-");
	*str = ft_strjoin(*str, (mode & S_IROTH) ? "r" : "-");
	*str = ft_strjoin(*str, (mode & S_IWOTH) ? "w" : "-");
	*str = ft_strjoin(*str, (mode & S_IXOTH) ? "x" : "-");
}

void		find_tipe(char *p, mode_t mode)
{
	if (S_ISBLK(mode))
		*p = 'b';
	else if (S_ISCHR(mode))
		*p = 'c';
	else if (S_ISDIR(mode))
		*p = 'd';
	else if (S_ISREG(mode))
		*p = '-';
	else if (S_ISFIFO(mode))
		*p = 'f';
	else if (S_ISLNK(mode))
		*p = 'l';
	else if (S_ISSOCK(mode))
		*p = 's';
	else
		*p = '?';
}

int			find_a(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 'a')
			return (1);
		key = key->next;
	}
	return (0);
}

int			find_r(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 'r')
			return (1);
		key = key->next;
	}
	return (0);
}

void		rostring(t_name **name)
{
	t_name	*tmp;
	t_name	*p;
	t_name	*head;
	int		len;
	int		i;

	tmp = NULL;
	len = len_name(*name);
	while (len > 0)
	{
		i = len;
		head = *name;
		while (i-- > 1)
			head = head->next;
		p = head;
		p->next = NULL;
		add_tmp(&tmp, p);
		len--;
	}
	*name = tmp;
}
