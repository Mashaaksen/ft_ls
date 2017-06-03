/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 01:53:51 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/02 14:16:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	char	*pp;
	int		i;

	if (s && f)
	{
		if ((p = ft_strnew(ft_strlen(s))))
		{
			pp = p;
			i = 0;
			while (*s)
			{
				*p++ = (*f)(i, *s);
				s++;
				i++;
			}
			return (pp);
		}
	}
	return (NULL);
}
