#include "ft_ls.h"

char    *ft_tolower_all(char *str)//Мать твою, оформи функцию АДЕКВАТНО!!!!!!!
{
    char *new;
    int i = -1;

    new = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
    while (++i < ft_strlen(str))
        new[i] = (int)ft_tolower(str[i]);
    new[i] = '\0';
    return (new);
}

int     ft_alpha_comp(t_files *curr_file, t_files *new_file)//АНАЛОГИЧНО!!!!!!!!!
{
	if (ft_strcmp(curr_file->file, new_file->file) < 0)
		return (1);
	return (0);
}

int     ft_time_comp(t_files *curr_file, t_files *new_file)
{
    if (curr_file->buf.st_mtimespec.tv_sec > new_file->buf.st_mtimespec.tv_sec)
        return (1);
    if (curr_file->buf.st_mtimespec.tv_sec == new_file->buf.st_mtimespec.tv_sec)
    {
        if (curr_file->buf.st_mtimespec.tv_nsec > new_file->buf.st_mtimespec.tv_nsec)
            return (1);
        if (curr_file->buf.st_mtimespec.tv_nsec == new_file->buf.st_mtimespec.tv_nsec)
            return (ft_alpha_comp(curr_file, new_file) ? 1 : 0);
    }
    return (0);
}

//переделать функцию, в текущей версии сортировка условная
t_files *ft_insert_files(t_files *files, t_files *new_files, t_keys keys)
{
    t_files *head;
    int     vect_sort;
    int     choose_func;
    ft_compare_type compare_elem;

    vect_sort = keys.revers ? 0 : 1;
    compare_elem = keys.time ? ft_time_comp : ft_alpha_comp;
    head = files;
    if (!files || (files && compare_elem(files, new_files) != vect_sort))
    {
        if (files)
            new_files->next = files;
        return new_files;
    }
    else
    {
        while (files)
        {
            if (!files->next || (compare_elem(files, new_files) == vect_sort && compare_elem(files->next, new_files) != vect_sort))
            {
                new_files->next = files->next;
                files->next = new_files;
                break ;
            }
            files = files->next;
        }
    }
    return head;
}