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

//void		add_terget(const t_path *path, t_char_list **tmp)
//{
//	ssize_t	k;
//	char	link_name[PATH_LEN];
//
//	k = readlink(path->av, link_name, PATH_LEN);
//	if (k >= PATH_LEN)
//		(*tmp)->target = ft_strdup("Wrong: link filename too long!");
//	else
//	{
//		if (k == -1)
//			(*tmp)->target = ft_strdup("invalid symbolic link!");
//		else
//		{
//			link_name[k] = '\0';
//			(*tmp)->target = ft_strdup(link_name);
//		}
//	}
//}

int			main(int ac, char **av)
{
	t_ls	ls;
//	struct winsize win;

	ac = 0;
	av++;
	find_keys(&ls, &av);
//	if (!ls.keys.key_one)
//	{
//		ioctl(0, TIOCGWINSZ, &win);
//		win.ws_col = 181;
//		ls.keys.ws_col = &win.ws_col;
//
//	}
	find_path(&ls, av);
	ft_ls(ls.path, ls.keys, NULL);
}
