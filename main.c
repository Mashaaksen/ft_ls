/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 13:25:23 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/16 13:25:24 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_time(t_time a, t_time b, char *path, char *tmp)
{
	if (a.tv_sec > b.tv_sec)
		return (1);
	if (a.tv_sec == b.tv_sec)
	{
		if (a.nansec > b.nansec)
			return (1);
		if (a.nansec == b.nansec)
			return (alpha(path, tmp) ? 1 : 0);
	}
	return (0);
}

void		ft_find_time(t_time *tmp, struct stat buff)
{
	char	*str_time;
	char 	*now_time;
	time_t timer;

	timer = time(NULL);
	str_time = ft_strdup(ctime(&buff.st_mtimespec.tv_sec));
	now_time = ctime(&timer);
	tmp->year = ft_atoi(ft_strrchr(str_time, ' '));
	if (tmp->year == ft_atoi(ft_strrchr(now_time, ' ')))
		tmp->year = 0;
	tmp->str_month = ft_strndup(ft_strchr(str_time, ' ') + 1, 3);
	tmp->day = ft_atoi(ft_strchr(ft_strchr(str_time, ' ') + 1, ' '));
	tmp->hour = ft_atoi(ft_strchr(str_time, ':') - 2);
	tmp->minute = ft_atoi(ft_strchr(str_time, ':') + 1);
	tmp->nansec = buff.st_mtimespec.tv_nsec;
	tmp->tv_sec = buff.st_mtimespec.tv_sec;
}

void		add_terget(const t_path *path, t_char_list **tmp)
{
	ssize_t	k;
	char	link_name[PATH_LEN];

	k = readlink(path->av, link_name, PATH_LEN);
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

int			main(int ac, char **av)
{
	t_ls	ls;
	struct winsize win;

	ac = 0;
	av++;
	find_keys(&ls, &av);
	find_path(&ls, av);
	if (!ls.keys.key_one)
	{
		ioctl(0, TIOCGWINSZ, &win);
//		win.ws_col = 353;
		ls.keys.ws_col = &win.ws_col;

	}
	ft_ls(ls.path, ls.keys, 0, NULL);
}
