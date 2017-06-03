#include "ft_ls.h"

int			find_a(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 'a')
			return (1);
		key = key->next;
	}
	return (0);
}

int			find_r(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 'r')
			return (1);
		key = key->next;
	}
	return (0);
}

void		find_last(t_name *name, t_name **tmp, int i)
{
	while (i-- > 1)
		name = name->next;
	*tmp = name;
	(*tmp)->next = NULL;
}

int 		len_name(t_name *name)
{
	int		i;

	i = 0;
	while (name != NULL)
	{
		i++;
		name = name->next;
	}
	return (i);
}

void		ft_print(t_ls *ls, int l, t_key *key)
{
	int 	a;
	int 	r;
	int 	i;
	t_name	*tmp;

	i = len_name(ls->names);
	r = (find_r(key) == 1 ? 1 : 0);
	a = (find_a(key) == 1 ? 1 : 0);
	while (ls->names != NULL && i >= 0)
	{
		if (r == 1)
			find_last(ls->names, &tmp, i);
		else
			tmp = ls->names;
		if ((*tmp->str == '.' && a == 1) || *tmp->str != '.')
		{
			if (l == 0)
				printf("%s\n", tmp->str);
			else
				printf("%c%s %2i %s  %s%8i %s %2i %i:%02i %s %i\n", tmp->tipe, tmp->mode, tmp->link, tmp->name_pw, tmp->name_gr, (int)tmp->size, tmp->time, tmp->time1.day, tmp->time1.hour, tmp->time1.minute, tmp->str, tmp->time1.sec);
		}
		r == 0 ? ls->names = ls->names->next : 0;
		i--;
	}
	printf("\n");
}

