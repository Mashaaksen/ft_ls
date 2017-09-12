#include "ft_ls.h"

char 		**create_2_args(char *av)
{
	char 	**args;
	char 	**a;
	int 	i;

	i = 0;
	args = (char **)malloc(sizeof(char *) * 3);
	if (!ft_strchr(av, '/'))
	{
		args[0] = "./";
		args[1] = av;
	}
	else
	{
		a = ft_strsplit(av, '/');
		args[0] = (*av == '/' ? "/" : "");
		if (*a)
		{
			while (a[i] && a[i + 1])
				args[0] = ft_strjoin(ft_strjoin(args[0], a[i++]), "/");
			args[1] = ft_strdup(a[i]);
		}
		else
			args[1] = NULL;
	}
	args[2] = NULL;
	return (args);
}

void 		check_right_path(char *av, t_dir *inform, t_path **tmp)
{
	char **args;

	args = create_2_args(av);
	inform->dir = opendir(args[0]);
	if (!inform->dir)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", av);
		exit(0);
	}
	else
		while (args[1] && (inform->entry = readdir(inform->dir)))
			if (!ft_strcmp(inform->entry->d_name, args[1]))
			{
				*tmp = (t_path *)malloc(sizeof(t_path));
				(*tmp)->av = av;
				(*tmp)->road = args[0];
				(*tmp)->file = args[1];
				lstat(av, &(*tmp)->buff);
				if (S_ISDIR((*tmp)->buff.st_mode))
					(*tmp)->type = 'd';
				else
					(*tmp)->type = 'f';
				break;
			}
	if (!args[1])
	{
		*tmp = (t_path *)malloc(sizeof(t_path));
		(*tmp)->av = av;
		(*tmp)->road = args[0];
		(*tmp)->file = args[1];
		(*tmp)->time.month = 13;
		(*tmp)->type = 'd';
	}
	if (!(*tmp))
	{
		ft_printf("ft_ls: %s: No such file or directory\n", av);
		exit(0);
	}
	closedir(inform->dir);
}

int			alpha(char *a, char *b)
{
	char	*s1;
	char	*s2;

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

int			find_month(char *str, int i)
{
	if (i++ && !ft_strcmp(str, "Jan"))
		return (i);
	if (i++ && !ft_strcmp(str, "Feb"))
		return (i);
	if (i++ && !ft_strcmp(str, "Mar"))
		return (i);
	if (i++ && !ft_strcmp(str, "Apr"))
		return (i);
	if (i++ && !ft_strcmp(str, "May"))
		return (i);
	if (i++ && !ft_strcmp(str, "Jun"))
		return (i);
	if (i++ && !ft_strcmp(str, "Jul"))
		return (i);
	if (i++ && !ft_strcmp(str, "Aug"))
		return (i);
	if (i++ && !ft_strcmp(str, "Sep"))
		return (i);
	if (i++ && !ft_strcmp(str, "Oct"))
		return (i);
	if (i++ && !ft_strcmp(str, "Nov"))
		return (i);
	if (i++ && !ft_strcmp(str, "Dec"))
		return (i);
	return (i);
}

void		ft_find_time(t_time *tmp, struct stat buff)
{
	char 	*time;
	char 	**a;
	char 	**b;

	if (tmp->month != 13)
	{
		time = ctime(&buff.st_mtimespec.tv_sec);
		a = ft_strsplit(time, ' ');
		tmp->month = find_month(a[1], 0);
		tmp->day = ft_atoi(a[2]);
		b = ft_strsplit(a[3], ':');
		time = a[1];
		tmp->hour = ft_atoi(b[0]);
		tmp->minute = ft_atoi(b[1]);
		tmp->sec = ft_atoi(b[2]);
	}
	else
		tmp->month = 0;
}

int			ft_time(t_time a, t_time b)
{
	if (a.month > b.month)
		return (1);
	if (a.month == b.month)
	{
		if (a.day > b.day)
			return (1);
		if (a.day == b.day)
		{
			if (a.hour > b.hour)
				return (1);
			if (a.hour == b.hour)
			{
				if (a.minute > b.minute)
					return (1);
				if (a.minute == b.minute)
					if (a.sec > b.sec)
						return (1);
			}
		}
	}
	return (0);
}

void 		add_and_sort(t_key keys, t_path **path, t_path *tmp)
{
	t_path	*head;

	if (*path == NULL)
		*path = tmp;
	else
	{
		if (keys.key_time == 0)
		{
			if (keys.key_rev == 0)
			{
				if (alpha((*path)->av, tmp->av))
				{
					tmp->next = *path;
					*path = tmp;
				}
				else
				{
					head = *path;
					while (*path && (*path)->next && !alpha((*path)->next->av, tmp->av))
						*path = (*path)->next;
					tmp->next = (*path)->next;
					(*path)->next = tmp;
					*path = head;
				}
			}
			else
			{
				if (!alpha((*path)->av, tmp->av))
				{
					tmp->next = *path;
					*path = tmp;
				}
				else
				{
					head = *path;
					while (*path && (*path)->next && alpha((*path)->next->av, tmp->av))
						*path = (*path)->next;
					tmp->next = (*path)->next;
					(*path)->next = tmp;
					*path = head;
				}
			}
		}
		else
		{
			ft_find_time(&tmp->time, tmp->buff);
			if (keys.key_rev == 0)
			{
				if (ft_time(tmp->time, (*path)->time))
				{
					tmp->next = *path;
					*path = tmp;
				}
				else
				{
					head = *path;
					while (*path && (*path)->next && !ft_time(tmp->time, (*path)->next->time))
						*path = (*path)->next;
					tmp->next = (*path)->next;
					(*path)->next = tmp;
					*path = head;
				}
			}
			else
			{
				if (!ft_time(tmp->time, (*path)->time))
				{
					tmp->next = *path;
					*path = tmp;
				}
				else
				{
					head = *path;
					while (*path && (*path)->next && ft_time(tmp->next->time, (*path)->next->time))
						*path = (*path)->next;
					tmp->next = (*path)->next;
					(*path)->next = tmp;
					*path = head;
				}
			}
		}
	}
}

void 		find_path(t_ls *ls, char **av)
{
	t_path	*tmp;

	ls->path = NULL;
	while (*av)
	{
		tmp = NULL;
		check_right_path(*av, &ls->inform, &tmp);
		add_and_sort(ls->keys, &ls->path, tmp);
		av++;
	}
}

