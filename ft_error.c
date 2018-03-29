/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:07:28 by maksenov          #+#    #+#             */
/*   Updated: 2018/03/23 18:07:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ft_error_keys(char c)
{
	write(1, "ft_ls: illegal option -- ", 25);
	write(1, &c, 1);
	write(1, "\nusage: ./ft_ls [-larRtug] [file ...]\n", 36);
	exit(2);
}

void	ft_error(char *str)
{
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
	exit(1);
}
