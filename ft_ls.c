#include "ft_ls.h"

void 		add_list(t_path *path, t_key *keys, t_char_list **list);

void		print_tipe(mode_t mode, char **str)
{
	*str = NULL;
	if (S_ISBLK(mode))
		*str = "b";
	else if (S_ISCHR(mode))
		*str = "c";
	else if (S_ISDIR(mode))
		*str = "d";
	else if (S_ISREG(mode))
		*str = "-";
	else if (S_ISFIFO(mode))
		*str = "f";
	else if (S_ISLNK(mode))
		*str = "l";
	else if (S_ISSOCK(mode))
		*str = "s";
	else
		*str = "*";
}

void		print_mode(mode_t mode, char **str)
{
	*str = "";
	*str = ft_strjoin(*str, ((mode & S_IRUSR) ? "r" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IWUSR) ? "w" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IXUSR) ? "x" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IRGRP) ? "r" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IWGRP) ? "w" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IXGRP) ? "x" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IROTH) ? "r" : "-"));
	*str = ft_strjoin(*str, ((mode & S_IWOTH) ? "w" : "-"));
	if (mode & S_ISVTX)
		*str = ft_strjoin(*str, "t");
	else if (mode & S_IXOTH)
		*str = ft_strjoin(*str, "x");
	else
		*str = ft_strjoin(*str, "-");
}

void 		print_file(t_path *path,t_key keys)
{

	t_char_list *list;

	list = NULL;
	while (path != NULL)
	{
		if (path->type == 'f')
		{

			if ((keys.key_all && *(path->file) == '.') || *(path->file) != '.') {
				if (!keys.key_list)
					ft_printf("%s\n", path->file);
				else {
					path->uid = getpwuid(path->buff.st_uid);
					path->gid = getgrgid(path->buff.st_gid);
					add_list(path, &keys, &list);
				}
			}
		}
		path = path->next;
	}
	while (list)
	{
		ft_printf("%s%s %*i %-*s  %-*s  %*i %s %2i %02i:%02i %s", list->tipe,
				  list->mode, keys.max_link + 1, list->st_nlink, keys.max_name_pw, list->pw_name,
				  keys.max_name_gr, list->gr_name, keys.max_size, (int)list->st_size, list->str_month,
				  list->day, list->hour, list->minute, list->av);
		if (*(list->tipe) == 'l')
			ft_printf(" -> %s\n", list->target);
		else
			ft_printf("\n");
		list = list->next;
	}
}

int 		read_all(t_path *path, t_path **tmp, t_key *key)
{
	t_dir	inform;
	t_path	*p;

	inform.dir = opendir(path->file ? ft_strjoin(path->road, ft_strjoin("/", path->file)) : path->road);
	if (!inform.dir)
		return (0);
	while ((inform.entry = readdir(inform.dir)))
	{
		p = (t_path *)malloc(sizeof(t_path));
		p->av = ft_strjoin(ft_strjoin(path->av, "/"), inform.entry->d_name);
		p->road = path->av;
		p->file = ft_strdup(inform.entry->d_name);
		p->next = NULL;
		lstat(p->av, &p->buff);
		key->count++;
		if (key->key_time || key->key_list)
			ft_find_time(&(p->time), p->buff);
		if (S_ISDIR(p->buff.st_mode))
			p->type = 'd';
		else
		{
			key->file = 1;
			p->type = 'f';
		}
		if ((key->key_all && *(p->file)  == '.') || *(p->file) != '.')
			key->total += p->buff.st_blocks;
		add_and_sort(*key, tmp, p);
	}
	closedir(inform.dir);
	return (1);
}

void 		add_list(t_path *path, t_key *keys, t_char_list **list)
{
	int		i;
	t_char_list *tmp;
	t_char_list *head;
	ssize_t 	k;
	char	link_name[PATH_LEN];

	k = 0;
	tmp = (t_char_list *)malloc(sizeof(t_char_list));
	print_tipe(path->buff.st_mode, &tmp->tipe);
	print_mode(path->buff.st_mode, &tmp->mode);
	tmp->st_nlink = path->buff.st_nlink;
	tmp->pw_name = ft_strdup(path->uid->pw_name);
	tmp->gr_name = ft_strdup(path->gid->gr_name);
	tmp->st_size = path->buff.st_size;
	tmp->str_month = path->time.str_month;
	tmp->day = path->time.day;
	tmp->hour = path->time.hour;
	tmp->minute = path->time.minute;
	tmp->file = path->file;
	tmp->av = path->av;
	i = (int)ft_strlen(ft_itoa_base((size_t)tmp->st_size, 'i'));
	if (i > keys->max_size)
		keys->max_size = i;
	i = (int)ft_strlen(ft_itoa_base((size_t)tmp->st_nlink, 'i'));
	if (i > keys->max_link)
		keys->max_link = i;
	i = (int)ft_strlen(tmp->pw_name);
	if (i > keys->max_name_pw)
		keys->max_name_pw = i;
	i = (int)ft_strlen(tmp->gr_name);
	if (i > keys->max_name_gr)
		keys->max_name_gr = i;
	tmp->next = NULL;
	if (*(tmp->tipe) == 'l')
	{
		k = readlink(path->av, link_name, PATH_LEN);
		if (k >= PATH_LEN)
			tmp->target = ft_strdup("Wrong: link filename too long!");
		else
		{
			if (k == -1)
				tmp->target = ft_strdup("invalid symbolic link!");
			else
			{
				link_name[k] = '\0';
				tmp->target = ft_strdup(link_name);
			}
		}
	}
	if (!*list)
		*list = tmp;
	else
	{
		head = *list;
		while (*list && (*list)->next)
			*list = (*list)->next;
		(*list)->next = tmp;
		*list = head;
	}
}

void 		print_all(t_path *path, t_key keys)
{
	t_char_list *list;

	list = NULL;
	while (path != NULL)
	{
		if ((keys.key_all && *(path->file)  == '.') || *(path->file) != '.')
		{
			if (!keys.key_list)
				ft_printf("%s\n", path->file);
			else
			{
				path->uid = getpwuid(path->buff.st_uid);
				path->gid = getgrgid(path->buff.st_gid);
				add_list(path, &keys, &list);
			}
		}
		path = path->next;
	}
	if (keys.key_list)
		ft_printf("total %i\n", keys.total);
	while (list)
	{
		ft_printf("%s%s %*i %-*s  %-*s  %*i %s %2i %02i:%02i %s", list->tipe,
				  list->mode, keys.max_link + 1, list->st_nlink, keys.max_name_pw, list->pw_name,
				  keys.max_name_gr, list->gr_name, keys.max_size, (int)list->st_size, list->str_month,
				  list->day, list->hour, list->minute, list->file);
		if (*(list->tipe) == 'l')
			ft_printf(" -> %s\n", list->target);
		else
			ft_printf("\n");
		list = list->next;
	}
}

void 		print_dir(t_path *path,t_key keys, int flag)
{
	t_path	*tmp;

	tmp = NULL;
	while (path)
	{
		if (path->type == 'd')
		{
			if (!path->file || ((keys.key_all || !flag) && *(path->file)  == '.') || *(path->file) != '.')
			{
				keys.total = 0;
				keys.max_link = 0;
				keys.max_size = 0;
				keys.max_name_gr = 0;
				keys.max_name_pw = 0;
				if (flag || keys.count > 1)
					ft_printf("%s:\n", path->av);
				if (read_all(path, &tmp, &keys))
				{
					print_all(tmp, keys);
					keys.key_recurs ? ft_ls(tmp, keys, flag + 1) : 0;
				}
				tmp = NULL;
			}
		}
		path = path->next;
	}
}

void 		ft_ls(t_path *path, t_key keys, int flag)
{
	keys.file && !flag? print_file(path, keys) : 0;
	print_dir(path, keys, flag);
}