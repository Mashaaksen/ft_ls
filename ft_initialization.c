#include "ft_ls.h"

void    ft_initialize_ls(t_ls *ls)
{
    ls->keys.all = 0;
    ls->keys.list = 0;
    ls->keys.recursive = 0;
    ls->keys.revers = 0;
    ls->keys.time = 0;
//    ls->keys.first_time = 0; Возможно не понадобится
    ls->files = NULL;
}


//ф-ция для создания новой ноды
t_files *ft_initialize_files(t_files *files, struct stat buf, char *name_file, char *full_path, t_keys keys)
{
    t_files *new_files;
    t_serv  serv;

    new_files = (t_files *)malloc(sizeof(t_files));
    new_files->buf = buf;
    new_files->file = name_file ? ft_strdup(name_file) : NULL;
    new_files->full_path = full_path ? ft_strdup(full_path) : ft_strdup(name_file);
    //Сделать тернарником!!!
    if (keys.list)
    {
        serv.group = getgrgid(buf.st_gid);
        serv.passwd = getpwuid(buf.st_uid);
        new_files->group = ft_strdup(serv.group->gr_name);
        new_files->pwd = ft_strdup(serv.passwd->pw_name);
    }
    else
    {
        new_files->group = NULL;
        new_files->pwd = NULL;
    }
    new_files->next = NULL;
    //вставляем новую ноду в необходимом порядке в существующий список
    files = ft_insert_files(files, new_files, keys);
    return (files);
}