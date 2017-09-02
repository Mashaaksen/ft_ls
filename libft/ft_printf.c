/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:41:43 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/24 18:20:08 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			find_spec(char *str)
{
	int		i;

	i = 0;
	while (*str != 's' && *str != 'S' && *str != 'p' && *str != 'd'
	&& *str != 'D' && *str != 'i' && *str != 'o' && *str != 'O'
	&& *str != 'u' && *str != 'U' && *str != 'x' && *str != 'X'
	&& *str != 'c' && *str != 'C' && *str != '\0')
	{
		str++;
		i++;
	}
	return (i + 1);
}

int			fill(const char *str, t_print *print, va_list ap)
{
	int		ret;

	ret = 0;
	while (*str != '\0')
	{
		full(&print);
		while (*str != '\0' && *str != '%')
		{
			ret++;
			write(1, &(*(str++)), 1);
		}
		if (*str == '%')
		{
			++str;
			str = proc(str, my_print(print, (char *) str), ap, &ret);
		}
	}
	return (ret);
}

void		full(t_print **print)
{
	(*print)->proc = 0;
	(*print)->weidth = 0;
	(*print)->plus = 0;
	(*print)->null = 0;
	(*print)->space = 0;
	(*print)->hash = 0;
	(*print)->mynus = 0;
	(*print)->accuracy = -1;
	(*print)->type = 0;
	(*print)->cost = 0;
	(*print)->size = NULL;
	(*print)->p = NULL;
	(*print)->fm = 0;
	(*print)->i = NULL;
}

int			ft_printf(const char *format, ...)
{
	t_print	print;
	va_list	ap;
	int		ret;

	if (format == NULL)
		return (0);
	va_start(ap, format);
	ret = fill(format, &print, ap);
	va_end(ap);
	return (ret);
}
