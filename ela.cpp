//int					check_file(char *str, DIR *dir, t_path **path_f)
//{
//	char			**a;
//	int				i;
//	struct stat		buff;
//	char 			*path;
//	struct dirent	*entry;
//	i = 0;
//	a = ft_strsplit(str, '/');
//	path = (*str == '/' ? "../" : "");
//	while (a[i] && a[i + 1])
//	{
//		path = ft_strjoin(ft_strjoin(path, a[i]), "/");
//		dir = opendir(path);
//		while ((entry = readdir(dir)) != NULL)
//			if (!ft_strcmp(entry->d_name, a[i + 1]))
//				break ;
//		if (entry == NULL || ft_strcmp(entry->d_name, a[i + 1]))
//			return (0);
//		if (a[i + 2] == NULL)
//		{
//			lstat(ft_strjoin(ft_strjoin(path, "/"), a[i + 1]), &buff);
//			if (S_ISDIR(buff.st_mode) == 0)
//			{
//				if (path[0] == '.' && path[1] == '.')
//					path += 2;
//				(*path_f)->str = ft_strdup(path);
//				(*path_f)->file = ft_strdup(a[i + 1]);
//			}
//			return (1);
//		}
//		closedir(dir);
//		i++;
//	}
//	return (0);
//}
//
//void				add_path(char *str, t_path **path)
//{
//	t_path			*tmp;
//	t_path			*p;
//	DIR				*dir;
//
//	p = (t_path *)malloc(sizeof(t_path));
//	p->str = ft_strdup(str);
//	p->next = NULL;
//	if ((dir = opendir(str)) == NULL)
//		if (check_file(str, NULL, &p) == 0)
//		{
//			ft_printf("ft_ls: %s: No such file or directory\n", str);
//			return ;
//		}
//	dir == NULL ? 0 : closedir(dir);
//	if (*path == NULL)
//		*path = p;
//	else
//	{
//		tmp = *path;
//		while (tmp->next != NULL)
//			tmp = tmp->next;
//		tmp->next = p;
//	}


//alias ft_ls="./ft_ls"

