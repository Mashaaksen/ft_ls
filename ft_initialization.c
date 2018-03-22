#include "ft_ls.h"

void    ft_initialize_length(t_keys *keys)
{
	keys->length_group = 0;
	keys->length_pwd = 0;
	keys->length_link = 0;
	keys->length_size = 0;
}

void    ft_initialize_ls(t_ls *ls)
{
    ls->keys.all = 0;
    ls->keys.list = 0;
    ls->keys.recursive = 0;
    ls->keys.revers = 0;
    ls->keys.time = 0;
    ls->keys.length_group = 0;
    ls->keys.length_pwd = 0;
    ls->keys.length_link = 0;
	ls->keys.length_size = 0;
//    ls->keys.first_time = 0; Возможно не понадобится
    ls->files = NULL;
}

char*		ft_add_terget(char *path)
{
	ssize_t	k;
	char	link_name[PATH_LEN];
	char*   target;

	k = readlink(path, link_name, PATH_LEN);
	if (k >= PATH_LEN)
		target = ft_strdup("Wrong: link filename too long!");
	else
	{
		if (k == -1)
			target = ft_strdup("invalid symbolic link!");
		else
		{
			link_name[k] = '\0';
			target = ft_strdup(link_name);
		}
	}
	return target;
}

//ф-ция для создания новой ноды
t_files *ft_initialize_files(t_files *files, struct stat buf, char *name_file, char *full_path, t_keys *keys)
{
    t_files *new_files;
    t_serv  serv;
    size_t len;
    
    len = 0;
    new_files = (t_files *)malloc(sizeof(t_files));
    new_files->buf = buf;
    new_files->file = name_file ? ft_strdup(name_file) : NULL;
    new_files->full_path = full_path ? ft_strdup(full_path) : ft_strdup(name_file);
    //Сделать тернарником!!!
    if (keys->list && (*name_file != '.' || keys->all || !ft_strcmp(name_file, full_path)))
    {
        serv.group = getgrgid(buf.st_gid);
        serv.passwd = getpwuid(buf.st_uid);
        new_files->group = ft_strdup(serv.group->gr_name);
        new_files->pwd = ft_strdup(serv.passwd->pw_name);
        len = ft_strlen(new_files->pwd);
        if (keys->length_pwd < len)
            keys->length_pwd = len;
        len = ft_strlen(new_files->group);
        if (keys->length_group < len)
            keys->length_group = len;
        len = (size_t)size_v(buf.st_nlink, 10);
	    if (keys->length_link < len)
		    keys->length_link = len;
	    len = (size_t)size_v((unsigned long long int) buf.st_size, 10);
	    if (keys->length_size < len)
		    keys->length_size = len;
	    if (S_ISLNK(buf.st_mode))
		    new_files->target = ft_add_terget(full_path);
		else
		    new_files->target = NULL;
    }
    else
    {
        new_files->group = NULL;
        new_files->pwd = NULL;
	    new_files->target = NULL;
    }
    new_files->next = NULL;
    //вставляем новую ноду в необходимом порядке в существующий список
    files = ft_insert_files(files, new_files, *keys);
    return (files);
}