/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:12 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:40:54 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*putstr_str(t_print *print, char *str)
{
	if ((print->type == 'd' || print->type == 'i') && print->plus == 1)
		str = ft_strjoin("+", str);
	else if ((print->type == 'd' || print->type == 'i') && print->space == 1
		&& *str != '-')
		str = ft_strjoin(" ", str);
	if ((print->type != 's' && !ft_strcmp(str, "l")) || (print->type == 's' &&
		ft_strcmp(str, "l")) || (print->type != 's' && ft_strcmp(str, "l")))
		str = flag_weidth(print, str);
	else if ((print->type == 'd' || print->type == 'i') && print->space == 1
		&& *str != '-')
		str = ft_strjoin(" ", str);
	if ((print->cost == 1 && print->mynus == 0) || (print->type != 'c' &&
		print->type != 'C') || ((print->type == 'c' || print->type == 'C')
		&& print->cost == 0))
		ft_putstr(str);
	return (str);
}

char		*str_accuracy(t_print *print, char *str)
{
	if (print->accuracy > 0 && ((print->type != 's' && !ft_strcmp(str, "l"))
		|| (print->type == 's' && ft_strcmp(str, "l")) || (print->type != 's'
		&& ft_strcmp(str, "l"))))
		str = accuracy(print, str);
	if (print->accuracy == 0 && print->type == 's')
		str = "";
	return (str);
}

int			ft_print(t_print *print, va_list ap)
{
	int		len;
	char	a;
	char	*str;

	str = 0;
	a = '\0';
	len = 0;
	str = find_str(print, ap);
	if (str != NULL || print->p != NULL)
	{
		str == NULL ? str = print->p : 0;
		str = str_accuracy(print, str);
		print->accuracy > 0 && print->type != 's' ? print->null = 0 : 0;
		*str == '-' ? print->plus = 0 : 0;
		str = putstr_str(print, str);
		len = (int)ft_strlen(str);
		if ((print->type != 'c' || print->type != 'C') && print->cost == 1)
		{
			len++;
			write(1, &a, 1);
			print->mynus == 1 ? ft_putstr(str) : 0;
		}
	}
	return (str != NULL ? len : 0);
}
