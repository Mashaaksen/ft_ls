/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 21:00:26 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/18 21:03:12 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_words(char const *s, char c)
{
	char	*p;
	int		cw;

	cw = 0;
	if (!*s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		p = (char *)s;
		while (*p != c && *p)
			p++;
		(*s != c && *s) ? cw++ : 0;
		s = p;
	}
	return (cw);
}
