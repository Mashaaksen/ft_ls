/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/03 15:18:12 by maksenov          #+#    #+#             */
/*   Updated: 2017/04/03 15:40:54 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_print		*check_type(const char **str, t_print *print)
{
	char	*p;
	char	*s;

	p = "sSpdDioOuUxXcC";
	s = ft_strchr(p, **str);
	if (s && **str != '\0')
	{
		print->type = *s;
		(*str)++;
		print->p++;
	}
	return (print);
}

int			check_count(char *p)
{
	int		i;

	i = 0;
	while (*p != '\0')
	{
		if (ft_strchr("sSpdDioOuUxXcC", *p))
			i++;
		p++;
	}
	return (i >= 2 ? 0 : 1);
}

int			check_all_check(char *p)
{
	if (ft_strchr(p, 's') == NULL &&
		ft_strchr(p, 'S') == NULL && ft_strchr(p, 'p') == NULL &&
		ft_strchr(p, 'd') == NULL
		&& ft_strchr(p, 'D') == NULL &&
		ft_strchr(p, 'i') == NULL && ft_strchr(p, 'o') == NULL &&
		ft_strchr(p, 'O') == NULL
		&& ft_strchr(p, 'u') == NULL &&
		ft_strchr(p, 'U') == NULL && ft_strchr(p, 'x') == NULL &&
		ft_strchr(p, 'X') == NULL
		&& ft_strchr(p, 'c') == NULL && ft_strchr(p, 'C') == NULL)
		return (0);
	return (1);
}

int			check_all(t_print *print, char **str)
{
	size_t	len;
	char	*p;

	len = 0;
	p = NULL;
	if (**str != '\0')
	{
		len = (ft_strchr(*str, '%') - *str);
		ft_strchr(*str, '%') == NULL ? len = (ft_strchr(*str, '\0') - *str) : 0;
		**str == '%' ? len = 0 : 0;
		p = (char *)malloc(sizeof(char) * len + 1);
		ft_memcpy(p, *str, len + 1);
		if ((check_all_check(p) == 0) || check_count(p) == 0)
		{
			print->p = (char *)malloc(sizeof(char) * 2);
			print->p[0] = *p;
			print->p[1] = '\0';
			(*str)++;
			free((void *)p);
			return (0);
		}
		free((void *)p);
	}
	return (1);
}
