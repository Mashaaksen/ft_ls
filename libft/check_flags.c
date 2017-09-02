/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:14:42 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:14:44 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print		*check_flag(const char **str, t_print *print)
{
	while (**str == ' ' || **str == '-' || **str == '+'
		|| **str == '0' || **str == '#')
	{
		if (**str == ' ')
			print->space = 1;
		else if (**str == '-')
			print->mynus = 1;
		else if (**str == '0')
			print->null = 1;
		else if (**str == '+')
			print->plus = 1;
		else if (**str == '#')
			print->hash = 1;
		(*str)++;
		print->p++;
	}
	return (print);
}
