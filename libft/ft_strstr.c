/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:55:06 by maksenov          #+#    #+#             */
/*   Updated: 2016/11/28 00:12:59 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	const char *b;
	const char *l;

	if (!*str2)
		return ((char*)str1);
	while (*str1)
	{
		b = str1;
		l = str2;
		while (*l && *b && *l == *b)
		{
			l++;
			b++;
		}
		if (!*l)
			return ((char*)str1);
		str1++;
	}
	return (NULL);
}
