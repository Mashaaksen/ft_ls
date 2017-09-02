/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:10:14 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:11:00 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print		*my_print(t_print *print, char *str)
{
	size_t	len;

	len = (ft_strchr(str, '%') - str);
	ft_strchr(str, '%') == NULL ? len = (ft_strchr(str, '\0') - str) : 0;
	*str == '%' ? len = 0 : 0;
	print->p = (char *)malloc(sizeof(char) * len + 1);
	ft_memcpy(print->p, str, len + 1);
	return (print);
}

char		*proc_2(const char *str, t_print *print, va_list ap, int **ret)
{
	if (*str == '%' && print->type == 0 && *print->p == *str)
	{
		print->proc = 1;
		**ret += ft_print(print, ap);
		return (char *)(++str);
	}
	else if (print->type != 0)
	{
		**ret += ft_print(print, ap);
		return (char *)(str);
	}
	else
	{
		**ret += ft_print(print, ap);
		return (char *)(str);
	}
}

char		*proc(const char *str, t_print *print, va_list ap, int *ret)
{
	while (*str != '\0')
	{
		print = change(check_type(&str, check_size(&str,
check_accuracy(&str, ap, check_width(&str, ap, check_flag(&str, print))))));
		if ((*str == '%' || *str == '\0') && print->type == 0
			&& *print->p != *str)
		{
			*ret += ft_print(print, ap);
			*str != '\0' ? str++ : 0;
			return (char *)(str);
		}
		else if ((*str == '%' && print->type == 0 && *print->p == *str)
			|| print->type != 0 || check_all(print, (char **)&str) == 0)
		{
			str = proc_2(str, print, ap, &ret);
			return (char *)(str);
		}
	}
	return (char *)(str);
}
