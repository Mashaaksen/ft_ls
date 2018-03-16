/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   accuracy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:12 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:40:54 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*accuracy_p(t_print *print, char *str, int ret)
{
	char	*p;
	int		i;

	i = 0;
	str += 2;
	ret = (int)(print->accuracy - ft_strlen(str));
	if (ret > 0)
	{
		p = ft_memalloc(ret + 1);
		ret--;
		while (ret-- >= 0)
			p[i++] = '0';
		p = ft_strjoin("0x", p);
		str = ft_strjoin(p, str);
	}
	else
		str = ft_strjoin("0x", str);
	return (str);
}

char		*accuracy_if(t_print *print, char *str, int ret)
{
	char	*p;

	if (print->type == 'p')
		str = accuracy_p(print, str, ret);
	else if (print->type == 's')
	{
		ret = print->accuracy;
		p = ft_memalloc(ret + 1);
		ret--;
		while (ret >= 0)
		{
			p[ret] = str[ret];
			ret--;
		}
		return (p);
	}
	return (str);
}

char		*accuracy_else(t_print *print, char *str, int flag, int ret)
{
	int		i;
	char	*p;

	i = 0;
	if ((print->type == 'd' || print->type == 'i' || print->type == 'x'
		|| print->type == 'X' || print->type == 'o' || print->type == 'u')
		&& ret > 0)
	{
		p = ft_memalloc(ret + 1);
		flag == 1 ? p[i++] = '-' : 0;
		while (ret-- > 0)
			p[i++] = '0';
		str = ft_strjoin(p, str);
		if ((print->type == 'x' || print->type == 'X') && print->hash == 1)
			str = ft_strjoin("0x", str);
	}
	else if (flag == 1)
		str = ft_strjoin("-", str);
	else if (print->type == 'p' || print->type == 's')
		str = accuracy_if(print, str, ret);
	return (str);
}

char		*accuracy(t_print *print, char *str)
{
	int		flag;
	char	*p;
	int		ret;

	ret = 0;
	p = str;
	flag = 0;
	if (*p == '-' && (print->type == 'd' || print->type == 'i' ||
		print->type == 'x' || print->type == 'X' ||
			print->type == 'o' || print->type == 'u'))
	{
		flag++;
		p++;
		ret++;
		str = ft_strdup(p);
	}
	ret = (int)(print->accuracy - ft_strlen(str));
	str = accuracy_else(print, str, flag, ret);
	return (str);
}
