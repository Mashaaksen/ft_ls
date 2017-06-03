/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 01:53:51 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/02 14:16:31 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*lst1;
	t_list	*lst2;
	t_list	*lst3;

	if (!lst || !f)
		return (NULL);
	lst3 = (*f)(lst);
	lst1 = ft_lstnew(lst3->content, lst3->content_size);
	if (lst1)
	{
		lst2 = lst1;
		lst = lst->next;
		while (lst)
		{
			lst3 = (*f)(lst);
			lst2->next = ft_lstnew(lst3->content, lst3->content_size);
			if (!(lst2->next))
				return (NULL);
			lst2 = lst2->next;
			lst = lst->next;
		}
	}
	return (lst1);
}
