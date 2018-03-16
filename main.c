#include "ft_ls.h"

void    ft_print_type(t_files *file)
{
    if (S_ISBLK(file->buf.st_mode))
        ft_printf("b");
    else if (S_ISCHR(file->buf.st_mode))
        ft_printf("c");
    else if (S_ISDIR(file->buf.st_mode))
        ft_printf("d");
    else if (S_ISREG(file->buf.st_mode))
        ft_printf("-");
    else if (S_ISFIFO(file->buf.st_mode))
        ft_printf("f");
    else if (S_ISLNK(file->buf.st_mode))
        ft_printf("l");
    else if (S_ISSOCK(file->buf.st_mode))
        ft_printf("s");
    else
        ft_printf("*");
}

void    ft_print_mode(t_files *file)
{
    ft_printf((file->buf.st_mode & S_IRUSR) ? "r" : "-");
    ft_printf((file->buf.st_mode & S_IWUSR) ? "w" : "-");
    ft_printf((file->buf.st_mode & S_IXUSR) ? "x" : "-");
    ft_printf((file->buf.st_mode & S_IRGRP) ? "r" : "-");
    ft_printf((file->buf.st_mode & S_IWGRP) ? "w" : "-");
    ft_printf((file->buf.st_mode & S_IXGRP) ? "x" : "-");
    ft_printf((file->buf.st_mode & S_IROTH) ? "r" : "-");
    ft_printf((file->buf.st_mode & S_IWOTH) ? "w" : "-");
    if (file->buf.st_mode & S_ISVTX)
        ft_printf("t");
    else if (file->buf.st_mode & S_IXOTH)
        ft_printf("x");
    else
        ft_printf("-");
}

void    ft_print_file(t_files *file, t_keys keys)
{
    if (!keys.list)
        ft_printf("%s\n", file->file);
    else
    {
        ft_print_type(file);
        ft_print_mode(file);
        ft_printf("%s\n", file->file);
    }
}

void    ft_print_list(t_files *files, t_keys keys)
{
    while (files)
    {
        if (*(files->file) != '.')
            ft_print_file(files, keys);
        files = files->next;
    }
}

void    ft_print_only_file(t_files *files, t_keys keys)
{
    while (files)
    {
        if (!S_ISDIR(files->buf.st_mode))
            ft_print_file(files, keys);
        files = files->next;
    }
}

void    ft_start_ls(t_files *files, t_keys keys)
{
    t_files *opens_folder;
    static int in_the_first_time = 0;
    int     total;

    opens_folder = NULL;
    if (!in_the_first_time++)
        ft_print_only_file(files, keys);
    while (files)
    {
        if (S_ISDIR(files->buf.st_mode) && ft_strcmp(files->file, ".") && ft_strcmp(files->file, "..") && (*(files->file) != '.' || !ft_strcmp(files->file, "./")))
        {
            total = 0;
            ft_printf("%s: \n", files->full_path);
            opens_folder = ft_opendir(files, keys, &total);
            if (keys.list && total)
                ft_printf("total %d\n", total);
            ft_print_list(opens_folder, keys);
            if (keys.recursive && opens_folder)
                ft_start_ls(opens_folder, keys);
        }
        files = files->next;
    }
}

int main(int ac, char **av)
{
    t_ls    ls;

    ft_initialize_ls(&ls);
    ft_verification_param(ac, av, &ls);
    //ls.keys.first_time = 1;
    ft_start_ls(ls.files, ls.keys);
    return 0;
}