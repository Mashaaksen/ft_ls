/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:12 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:40:54 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*find_size_p(t_print *print, char *str)
{
	if (print->type == 'p' && !ft_strstr(str, "0x"))
		str = ft_strjoin("0x", str);
	return (str);
}

char		*find_null(void *i, t_print *print, char *str)
{
	if (print->type == 's')
		str = (char *)i;
	else if (print->type == 'c' || print->type == 'C')
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (i == 0)
		{
			print->cost++;
			return ("\0");
		}
		str[0] = (char)i;
		str[1] = '\0';
	}
	else if (print->type == 'd' || print->type == 'i')
		str = ft_itoa_long((int)i);
	else if (print->type == 'p')
	{
		if (i == NULL)
			return ("0x0");
		str = ft_strjoin("0x",
			ft_itoa_base((unsigned long long)i, print->type));
	}
	else
		str = ft_itoa_base((unsigned int)i, print->type);
	return (str);
}

char		*find_size_2(void *i, t_print *print, char *str)
{
	if (!ft_strcmp(print->size, "l"))
	{
		if (print->type == 'd' || print->type == 'i')
			str = ft_itoa_long((long int)i);
		else if (print->type == 's')
			str = ft_wchar((wchar_t *)i, print);
		else
			str = ft_itoa_base((unsigned long int)i, print->type);
	}
	else if (!ft_strcmp(print->size, "j"))
	{
		if (print->type == 'd' || print->type == 'i')
			str = ft_itoa_long((intmax_t)i);
		else
			str = ft_itoa_base((uintmax_t)i, print->type);
	}
	else if (!ft_strcmp(print->size, "z"))
	{
		if (print->type == 'd' || print->type == 'i')
			str = ft_itoa_long((size_t)i);
		else
			str = ft_itoa_base((size_t)i, print->type);
	}
	return (str);
}

char		*find_size_1(void *i, t_print *print, char *str)
{
	if (!ft_strcmp(print->size, "hh"))
	{
		if (print->type == 'd' || print->type == 'i')
			str = ft_itoa_long((signed char)i);
		else
			str = ft_itoa_base((unsigned char)i, print->type);
	}
	else if (!ft_strcmp(print->size, "h"))
	{
		if (print->type == 'd' || print->type == 'i')
			str = ft_itoa_long((short int)i);
		else
			str = ft_itoa_base((unsigned short int)i, print->type);
	}
	else if (!ft_strcmp(print->size, "ll"))
	{
		if (print->type == 'd' || print->type == 'i')
			str = ft_itoa_long((long long int)i);
		else
			str = ft_itoa_base((unsigned long long int)i, print->type);
	}
	else
		str = find_size_2(i, print, str);
	str = find_size_p(print, str);
	return (str);
}

char		*find_str(t_print *print, va_list ap)
{
	char	*str;

	str = NULL;
	if (print->type != 0)
	{
		print->i = va_arg(ap, void *);
		if (print->i == NULL && print->type == 's')
			return ("(null)");
		if (print->i == NULL && print->accuracy == 0 && print->type == 'p')
			return ("0x");
		if (print->accuracy == 0 && print->i == 0 &&
				print->type != 'c' && print->type != 'C')
		{
			if (print->hash == 1 && print->type == 'x')
				print->hash = 0;
			return ("");
		}
		if (print->size == NULL && print->type != 0)
			str = find_null(print->i, print, str);
		else if (print->size != NULL && print->type != 0)
			str = find_size_1(print->i, print, str);
	}
	else if (print->type == 0 && print->proc == 1)
		str = "%";
	return (str);
}
