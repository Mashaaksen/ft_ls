#include "ft_ls.h"

void		forward_time(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && !ft_time(tmp->time, (*path)->next->time))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		back_time(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && ft_time(tmp->next->time, (*path)->next->time))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		time_sort(t_key keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	head = NULL;
	if (keys.key_rev == 0)
	{
		if (ft_time(tmp->time, (*path)->time))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			forward_time(path, tmp, head);
	}
	else
	{
		if (!ft_time(tmp->time, (*path)->time))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			back_time(path, tmp, head);
	}
}

void		forward_alpha(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && !alpha((*path)->next->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void		back_alpha(t_path **path, t_path *tmp, t_path *head)
{
	head = *path;
	while (*path && (*path)->next && alpha((*path)->next->av, tmp->av))
		*path = (*path)->next;
	tmp->next = (*path)->next;
	(*path)->next = tmp;
	*path = head;
}

void 		alpha_sort(t_key keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	head = NULL;
	if (keys.key_rev == 0)
	{
		if (alpha((*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			forward_alpha(path, tmp, head);
	}
	else
	{
		if (!alpha((*path)->av, tmp->av))
		{
			tmp->next = *path;
			*path = tmp;
		}
		else
			back_alpha(path, tmp, head);
	}
}

void 		add_and_sort(t_key keys, t_path **path, t_path *tmp)
{
	if (*path == NULL)
		*path = tmp;
	else
	{
		if (keys.key_time == 0)
			alpha_sort(keys, path, tmp);
		else
			time_sort(keys, path, tmp);
	}
}


