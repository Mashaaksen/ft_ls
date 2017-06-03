/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 19:08:50 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/15 15:31:15 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	if (!(ft_strchr(str, c)))
		return (NULL);
	while (*str)
		str++;
	while (*str != c)
		str--;
	return ((char*)str);
}
