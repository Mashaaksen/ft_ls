/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:11:29 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:11:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print		*check_check(t_print *print)
{
	if ((print->type == 'd' || print->type == 'i' || print->type == 'o'
		|| print->type == 'x' || print->type == 'X')
		&& print->accuracy >= 0 && print->null == 1)
		print->null = 0;
	return (print);
}

t_print		*change(t_print *print)
{
	if (print->type == 'S' || print->type == 'D'
		|| print->type == 'O' || print->type == 'U')
	{
		print->size = ft_strdup("l");
		if (print->type == 'S')
			print->type = 's';
		else if (print->type == 'D')
			print->type = 'd';
		else if (print->type == 'O')
			print->type = 'o';
		else if (print->type == 'U')
			print->type = 'u';
	}
	print = check_check(print);
	return (print);
}
