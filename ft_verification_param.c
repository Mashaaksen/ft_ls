/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verification_param.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:18:15 by maksenov          #+#    #+#             */
/*   Updated: 2018/03/23 18:18:16 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_file_search(char *param, t_ls *ls)
{
	int			errnum;
	struct stat	buf;
	char		*temp;

	errnum = lstat(param, &buf);
	if (errnum != 0)
	{
		temp = ft_strjoin("ft_ls: ", param);
		perror(temp);
		free(temp);
	}
	else
		ls->files = ft_initialize_files(ls->files, buf, param, NULL, &ls->keys);
}

void			ft_keys_search(char *param, t_ls *ls)
{
	int			iter;

	iter = 1;
	while (param[iter])
	{
		if (param[iter] == 'l' || param[iter] == 'R' || param[iter] == 'a' ||
			param[iter] == 'r' || param[iter] == 't')
		{
			if (param[iter] == 'l')
				ls->keys.flags |= mask_l;
			else if (param[iter] == 'R')
				ls->keys.flags |= mask_R;
			else if (param[iter] == 'a')
				ls->keys.flags |= mask_a;
			else if (param[iter] == 'r')
				ls->keys.flags |= mask_r;
			else if (param[iter] == 't')
				ls->keys.flags |= mask_t;
			iter++;
		}
		else
			ft_error_keys(param[iter]);
	}
}

void			ft_verification_param(int ac, char **av, t_ls *ls)
{
	int			iter;
	int			count;

	count = 0;
	iter = 1;
	while (iter < ac)
	{
		if (*(av[iter]) == '-' && ft_strlen(av[iter]) > 1)
			ft_keys_search(av[iter], ls);
		else
		{
			count++;
			ft_file_search(av[iter], ls);
		}
		iter++;
	}
	if (!ls->files && !count)
	{
		struct stat buf;
		lstat(".", &buf);
		ls->files = ft_initialize_files(ls->files, buf, ".", ".", &ls->keys);
	}
}
