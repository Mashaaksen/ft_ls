/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:14:09 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:14:28 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print		*check_width(const char **str, va_list ap, t_print *print)
{
	if ((**str >= 49 && **str <= 57) || **str == 42)
	{
		if (**str == 42)
		{
			print->weidth = va_arg(ap, int);
			(*str)++;
			print->p++;
		}
		else
		{
			print->weidth = ft_atoi(*str);
			while (**str >= 48 && **str <= 57)
			{
				print->p++;
				(*str)++;
			}
		}
		if (print->weidth < 0)
		{
			print->mynus = 1;
			print->weidth *= -1;
		}
	}
	return (print);
}
