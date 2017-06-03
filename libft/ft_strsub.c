/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 01:59:01 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/05 12:43:09 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*dest;

	if (!s || !(dest = (char *)malloc(len + 1))
			|| (start > (unsigned int)ft_strlen(s)))
		return (NULL);
	else
	{
		dest = ft_strncpy(dest, (s + start), len);
		dest[len] = '\0';
	}
	return (dest);
}
