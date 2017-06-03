/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 01:53:51 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/02 14:16:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*new_link;

	if (!(new_link = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		new_link->content = NULL;
		new_link->content_size = 0;
	}
	else
	{
		if (!(new_link->content =
							(void *)malloc(sizeof(char *) * content_size)))
			return (NULL);
		new_link->content_size = content_size;
		ft_memcpy(new_link->content, content, content_size);
	}
	new_link->next = NULL;
	return (new_link);
}
