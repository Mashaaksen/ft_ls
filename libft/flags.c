/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 16:04:04 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 16:19:44 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*flag_sign(t_print *print, char *str, int fm)
{
	if (fm != 0 || print->plus != 0 || print->space != 0)
	{
		fm != 0 ? str = ft_strjoin("-", str) : 0;
		print->plus != 0 ? str = ft_strjoin("+", str) : 0;
		print->space != 0 ? str = ft_strjoin(" ", str) : 0;
	}
	return (str);
}

char		*flag_ret_else(t_print *print, char *str, int ret)
{
	char	*p;
	int		i;

	i = 0;
	if (print->null == 1 && print->hash == 0)
	{
		if (*str == '-' || *str == '+' || *str == ' ')
		{
			*str == '-' ? print->fm++ : 0;
			str++;
		}
		p = ft_memalloc((size_t)(ret + 1));
		while (ret-- > 0)
			p[i++] = '0';
		if (print->type == 'p')
			str = ft_strjoin(str, p);
		else
			str = ft_strjoin(p, str);
		str = flag_sign(print, str, print->fm);
	}
	p = ft_memalloc((size_t)(ret + 1));
	while (ret-- > 0)
		p[i++] = ' ';
	str = (str != NULL ? ft_strjoin(p, str) : p);
	return (str);
}

char		*flag_else(t_print *print)
{
	char	*s;

	s = NULL;
	if (print->type == 'o')
		s = "0";
	else if (print->type == 'x' || print->type == 'X')
	{
		if (print->type == 'x')
			s = "0x";
		else
			s = "0X";
	}
	return (s);
}

char		*flag_ret(t_print *print, char *str, int ret)
{
	char	*p;
	int		i;

	i = 0;
	if (print->hash == 1)
	{
		if (print->null == 1 && print->mynus == 0)
		{
			p = ft_memalloc((size_t)(ret + 1));
			while (ret-- > 0)
				p[i++] = '0';
			str = ft_strjoin(p, str);
		}
		flag_else(print) != NULL ? str = ft_strjoin(flag_else(print), str) : 0;
	}
	if (print->mynus == 1)
	{
		p = ft_memalloc((size_t)(ret + 1));
		while (ret-- > 0)
			p[i++] = ' ';
		str = ft_strjoin(str, p);
	}
	else
		str = flag_ret_else(print, str, ret);
	return (str);
}

char		*flag_weidth(t_print *print, char *str)
{
	int		sizeline;
	int		ret;

	sizeline = (int)(str != NULL ? ft_strlen(str) : 0);
	ret = print->weidth - sizeline;
	if (print->cost == 1)
		ret--;
	if (print->type == 'o' && print->hash == 1)
		ret--;
	else if ((print->type == 'x' || print->type == 'X') && print->hash == 1)
		ret -= 2;
	if (ret > 0)
		str = flag_ret(print, str, ret);
	else if (print->hash == 1 && *str != '0' && flag_else(print) != NULL)
		str = ft_strjoin(flag_else(print), str);
	return (str);
}
