/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 18:10:00 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/18 20:30:12 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_len_char(char const *s, char c)
{
	char	*p;

	if (!*s)
		return (0);
	while (*s == c && *s)
		s++;
	p = (char *)s;
	while (*p != c && *p)
		p++;
	return (p - s);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**res;
	char	*p1;
	char	**p2;

	if (!s || !(res = malloc(sizeof(char*) * (ft_count_words(s, c) + 1))))
		return (NULL);
	p2 = res;
	while (*s)
	{
		while (*s == c && *s && s++)
			;
		if (*s)
		{
			if (!(p1 = malloc(ft_len_char(s, c) + 1)))
				return (NULL);
			*res = p1;
			while (*s != c && *s && (*p1++ = *s++))
				;
			*p1 = '\0';
			res++;
		}
	}
	*res = NULL;
	return (p2);
}
