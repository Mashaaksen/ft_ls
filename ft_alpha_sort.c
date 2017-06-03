#include "ft_ls.h"

int 		alpha(char *a, char *b)
{
	char 	*s1;
	char 	*s2;

	s1 = a;
	s2 = b;
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
			return (*s1 > *s2 ? 1 : 0);
		*s1 != '\0' ? s1++ : 0;
		*s2 != '\0' ? s2++ : 0;
	}
	return (0);
}

int 		check_sort(t_name *name)
{
	t_name	*tmp;

	tmp = name->next;
	while (tmp != NULL)
	{
		if (alpha(name->str, tmp->str) == 1)
			return (0);
		name = name->next;
		tmp = tmp->next;
	}
	return (1);
}

void		ft_alpha_sort(t_name **name)
{
	t_name	*tmp;
	t_name	*p;
	t_name	*r;
	int 	i;

	while (check_sort(*name) != 1)
	{
		i = 0;
		r = *name;
		tmp = *name;
		p = tmp->next;
		while (p != NULL)
		{
			if (alpha(tmp->str, p->str) == 1)
			{
				i != 0 ? r->next = p : 0;
				i == 0 ? r = p : 0;
				tmp->next = p->next;
				p->next = tmp;
				tmp = (i != 0 ? r->next : r);
				i == 0 ? *name = r : 0;
				p = tmp->next;
			}
			if (i++ != 0)
				r = r->next;
			p = p->next;
			tmp = tmp->next;
		}
	}
}

