/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 01:53:51 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/18 20:33:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_int_min(int n)
{
	return (n < 0 ? -n : n);
}

static int		ft_len_int(int n)
{
	int len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int				len;
	unsigned int	num;
	char			*str;

	len = 0;
	len = ft_len_int(n);
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (0);
	str[len--] = '\0';
	num = ft_int_min(n);
	while (len >= 0)
	{
		str[len--] = num % 10 + 48;
		num = num / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
