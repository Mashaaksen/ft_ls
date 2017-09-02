/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wchar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:12 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:40:54 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			size_str(wchar_t *str)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (str[i])
	{
		if (str[i] <= 0x7F)
			size += 1;
		else if (str[i] <= 0x7FF)
			size += 2;
		else if (str[i] <= 0xFFFF)
			size += 3;
		else if (str[i] <= 0x10FFFF)
			size += 4;
		i++;
	}
	return (size);
}

void		print_wchar(wchar_t c, char *str, int *i, int *len)
{
	if (c <= 0x7F && 1 <= (*len)--)
		str[++(*i)] = (char)c;
	else if (c <= 0x7FF && (*len) >= 2)
	{
		str[++(*i)] = (char)((c >> 6) + 0xC0);
		str[++(*i)] = (char)((c & 0x3F) + 0x80);
		(*len) -= 2;
	}
	else if (c <= 0xFFFF && (*len) >= 3)
	{
		str[++(*i)] = (char)((c >> 12) + 0xE0);
		str[++(*i)] = (char)(((c >> 6) & 0x3F) + 0x80);
		str[++(*i)] = (char)((c & 0x3F) + 0x80);
		(*len) -= 3;
	}
	else if (c <= 0x10FFFF && (*len) >= 4)
	{
		str[++(*i)] = (char)((c >> 18) + 0xF0);
		str[++(*i)] = (char)(((c >> 12) & 0x3F) + 0x80);
		str[++(*i)] = (char)(((c >> 6) & 0x3F) + 0x80);
		str[++(*i)] = (char)((c & 0x3F) + 0x80);
		(*len) -= 4;
	}
}

char		*ft_wchar(wchar_t *str, t_print *print)
{
	int		j;
	int		i;
	char	*p;
	int		size;

	i = 0;
	j = -1;
	size = size_str(str);
	if (print->accuracy != -1 && print->accuracy < size)
		size = print->accuracy;
	p = (char *)malloc(sizeof(char) * (size + 1));
	p[size] = '\0';
	while (str[i] && size != 0)
		print_wchar(str[i++], p, &j, &size);
	p[++j] = '\0';
	return (p);
}
