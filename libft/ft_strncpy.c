/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 01:53:51 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/02 14:16:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	char *d;
	char *s;

	d = (char *)dest;
	s = (char *)src;
	while (*s && len > 0)
	{
		*d++ = *s++;
		len--;
	}
	while (len > 0)
	{
		*d++ = '\0';
		--len;
	}
	return (dest);
}
