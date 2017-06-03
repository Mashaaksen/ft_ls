/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 01:53:51 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/02 14:16:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *src, const void *dst, size_t n)
{
	if (!src && !dst && !n)
		return (0);
	while (n--)
	{
		if (*((unsigned char*)src) != *((unsigned char*)dst))
			return (*((unsigned char*)src) - *((unsigned char*)dst));
		src++;
		dst++;
	}
	return (0);
}
