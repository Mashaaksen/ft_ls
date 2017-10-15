/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 18:47:45 by maksenov          #+#    #+#             */
/*   Updated: 2017/10/15 18:47:46 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *sorc, size_t n)
{
	char	*dup;

	if (!(dup = (char *)malloc(sizeof(char) * n + 1)))
		return (NULL);
	dup = ft_strncpy(dup, sorc, n);
	dup[n] = '\0';
	return (dup);
}
