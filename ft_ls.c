#include "ft_ls.h"

void		print_tipe(mode_t mode)
{
	if (S_ISBLK(mode))
		ft_printf("b");
	else if (S_ISCHR(mode))
		ft_printf("c");
	else if (S_ISDIR(mode))
		ft_printf("d");
	else if (S_ISREG(mode))
		ft_printf("-");
	else if (S_ISFIFO(mode))
		ft_printf("f");
	else if (S_ISLNK(mode))
		ft_printf("l");
	else if (S_ISSOCK(mode))
		ft_printf("s");
	else
		ft_printf("?");
}

void		print_mode(mode_t mode)
{
	ft_printf((mode & S_IRUSR) ? "r" : "-");
	ft_printf((mode & S_IWUSR) ? "w" : "-");
	ft_printf((mode & S_IXUSR) ? "x" : "-");
	ft_printf((mode & S_IRGRP) ? "r" : "-");
	ft_printf((mode & S_IWGRP) ? "w" : "-");
	ft_printf((mode & S_IXGRP) ? "x" : "-");
	ft_printf((mode & S_IROTH) ? "r" : "-");
	ft_printf((mode & S_IWOTH) ? "w" : "-");
	ft_printf((mode & S_IXOTH) ? "x" : "-");
}

void 		print_file(t_path *path,t_key keys)
{
	while (path != NULL)
	{
		if (path->type == 'f')
		{
			if (!keys.key_list)
				ft_printf("%s\n", path->file);
			else {
				path->uid = getpwuid(path->buff.st_uid);
				path->gid = getgrgid(path->buff.st_gid);
				print_tipe(path->buff.st_mode);
				print_mode(path->buff.st_mode);
				ft_printf(" %i %s %s %i %s %i %i:%i %s", path->buff.st_nlink, path->uid->pw_name, path->gid->gr_name,
						  (int) path->buff.st_size, path->time.str_month, path->time.day, path->time.hour,
						  path->time.minute, path->av);
			}
		}
		path = path->next;
	}
}

void 		read_all(t_path *path, t_path **tmp, t_key *key)
{
	t_dir	inform;
	t_path	*p;

	inform.dir = opendir(path->file ? ft_strjoin(path->road, ft_strjoin("/", path->file)) : path->road);
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
		add_and_sort(*key, tmp, p);
	}
}

void 		print_all(t_path *path,t_key keys)
{
	while (path != NULL)
	{
		if ((keys.key_all && *(path->file)  == '.') || *(path->file) != '.')
		{
			if (!keys.key_list)
				ft_printf("%s\n", path->file);
			else {
				path->uid = getpwuid(path->buff.st_uid);
				path->gid = getgrgid(path->buff.st_gid);
				print_tipe(path->buff.st_mode);
				print_mode(path->buff.st_mode);
				ft_printf(" %i %s %s %i %s %i %i:%i %s", path->buff.st_nlink, path->uid->pw_name, path->gid->gr_name,
						  (int) path->buff.st_size, path->time.str_month, path->time.day, path->time.hour,
						  path->time.minute, path->av);
			}
		}
		path = path->next;
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
			if (!path->file || (keys.key_all && *(path->file)  == '.') || *(path->file) != '.')
			{
				if (flag || keys.count > 1)
					ft_printf("%s:\n", path->av);
				read_all(path, &tmp, &keys);
				print_all(tmp, keys);
				ft_printf("\n");
				keys.key_recurs ? ft_ls(tmp, keys, ++flag) : 0;
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