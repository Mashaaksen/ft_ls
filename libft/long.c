/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:12 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:40:54 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long		ft_int_min(long long n)
{
	return (n < 0 ? -n : n);
}

int				ft_len_int(long long n)
{
	int			len;

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

char			*ft_itoa_long(long long n)
{
	int			len;
	long long	num;
	char		*str;

	len = 0;
	len = ft_len_int(n);
	str = ft_memalloc((size_t)(len + 1));
	len--;
	num = ft_int_min(n);
	while (len >= 0)
	{
		if (n < 0 && len == 0)
		{
			len--;
			str[0] = '-';
		}
		else if (num % 10 < 0)
			str[len--] = (char)(num % 10 * -1 + 48);
		else
			str[len--] = (char)(num % 10 + 48);
		num = num / 10;
	}
	return (str);
}
