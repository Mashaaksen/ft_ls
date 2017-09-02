/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:57:53 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:57:55 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		error_option(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	write(1, &c, 1);
	ft_putstr("\n");
	ft_putstr("usage: ft_ls [-lRart] [file ...]");
	ft_putstr("\n");
	exit(0);
}

void		check_keys(char *str, t_key **key)
{
	while (*str)
	{
		*str == '-' ? str++ : 0;
		if (*str != 'l' && *str != 'R' && *str != 'a' && *str != 'r'
			&& *str != 't')
			error_option(*str);
		add_keys(key, *str);
		str++;
	}
}