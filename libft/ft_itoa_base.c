/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 09:55:35 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:17:27 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			size_v(unsigned long long value, int base)
{
	int size;

	size = 0;
	value == 0 ? size++ : 0;
	while (value != 0)
	{
		value /= base;
		size++;
	}
	return (size);
}

char		*ft_itoa_base(unsigned long long value, char c)
{
	int		size;
	char	*str;
	int		base;

	base = 10;
	if (c == 'x' || c == 'X' || c == 'p')
		base = 16;
	if (c == 'o')
		base = 8;
	size = size_v(value, base);
	str = (char *)malloc(sizeof(char) * size + 1);
	str[size--] = '\0';
	while (size >= 0)
	{
		if (value % base >= 10 && c == 'X')
			str[size--] = (char)(value % base + 55);
		else if (value % base >= 10 && (c == 'x' || c == 'o' || c == 'p'))
			str[size--] = (char)(value % base + 87);
		else
			str[size--] = (char)(value % base + 48);
		value /= base;
	}
	return (str);
}
