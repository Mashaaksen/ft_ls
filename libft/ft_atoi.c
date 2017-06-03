/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 12:41:17 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/18 20:36:19 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int	si;
	int	res;

	res = 0;
	si = 1;
	if (!(*str))
		return (0);
	while (*(char *)str == ' ' || *(char *)str == '\f' || *(char *)str == '\r'
			|| *(char *)str == '\v' || *(char *)str == '\n'
			|| *(char *)str == '\t')
		str++;
	if (*(char *)str == '-' || *(char *)str == '+')
	{
		si = (*(char *)str == '-' ? -1 : 1);
		str++;
	}
	while (ft_isdigit(*str))
	{
		res = res * 10 + *(char *)str - '0';
		str++;
	}
	return (res * si);
}
