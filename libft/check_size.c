/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:19:03 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:36:36 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print		*find_s(const char ***str, t_print *print)
{
	char	*p;
	int		i;

	if (***str == 'l' || ***str == 'h' || ***str == 'z' || ***str == 'j')
	{
		i = find_spec((char *)**str);
		p = (char *)malloc(sizeof(char) * i);
		p = ft_strncpy(p, (char *)**str, (size_t)i - 1);
		if (ft_strstr(p, "z"))
			print->size = ft_strdup("z");
		else if (ft_strstr(p, "j"))
			print->size = ft_strdup("j");
		else if (ft_strstr(p, "ll"))
			print->size = ft_strdup("ll");
		else if (ft_strstr(p, "l"))
			print->size = ft_strdup("l");
		else if (ft_strstr(p, "h"))
		{
			if (ft_strstr(p, "hh"))
				print->size = ft_strdup("hh");
			else
				print->size = ft_strdup("h");
		}
	}
	return (print);
}

t_print		*check_size(const char **str, t_print *print)
{
	print = find_s(&str, print);
	while (**str == 'l' || **str == 'h' || **str == 'z' || **str == 'j')
	{
		print->p++;
		(*str)++;
	}
	return (print);
}
