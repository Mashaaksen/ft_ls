/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 11:59:13 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/18 20:29:37 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	*ft_memcpy_rev(void *dest, const void *sorc, size_t n)
{
	char *s;
	char *d;

	s = (char *)sorc;
	d = (char *)dest;
	while (n--)
		d[n] = s[n];
	return (dest);
}

void			*ft_memmove(void *dest, const void *sorc, size_t n)
{
	(sorc > dest) ? ft_memcpy(dest, sorc, n) : ft_memcpy_rev(dest, sorc, n);
	return (dest);
}
