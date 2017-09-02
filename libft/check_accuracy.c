/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_accuracy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:11:52 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:13:30 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print		*check_accuracy(const char **str, va_list ap, t_print *print)
{
	if (**str == '.')
	{
		print->p++;
		(*str)++;
		if (**str == 42)
		{
			print->accuracy = va_arg(ap, int);
			(*str)++;
			print->p++;
		}
		else
		{
			print->accuracy = ft_atoi(*str);
			while (**str >= 48 && **str <= 57)
			{
				print->p++;
				(*str)++;
			}
		}
	}
	return (print);
}
