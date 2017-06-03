/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/18 20:31:23 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/18 20:31:24 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *s;
	char *d;

	s = (char *)src;
	d = (char *)dst;
	while (n--)
		*d++ = *s++;
	return (dst);
}
