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

void   ft_print_time(struct stat buf)
{
    char *new_str;
    char *curr_str;
    char **arr;

    curr_str = ctime(&buf.st_mtimespec.tv_sec);
    arr = ft_strsplit(curr_str, ' ');
    new_str = NULL;
    new_str = ft_strjoin(ft_strjoin(arr[1], " "), ft_strjoin(arr[2], " "));
    ft_printf(" %s %2s ", arr[1], arr[2]);
    //Больше равно полгода, вроде ещё на 3с сделать проверку.
    //Странная дичь при выводе на экран.
    if (time(NULL) - buf.st_mtimespec.tv_sec >= 15770000)//Возможно переделать метод определения.
        ft_printf("%5s ", ft_strsplit(arr[4], '\n')[0]);
    else
    {
        char **new_arr = ft_strsplit(arr[3], ':');
        ft_printf("%02i:%02i ", ft_atoi(new_arr[0]), ft_atoi(new_arr[1]));
    }
}

void    ft_print_file(t_files *file, t_keys keys)
{
    if (!keys.list)
        ft_printf("%s\n", file->file);
    else
    {
        ft_print_type(file);
        ft_print_mode(file);
        ft_printf(" %*d", keys.length_link, file->buf.st_nlink);//не забыть убрать пробелы, это выравнивание
        ft_printf(" %-*s %-*s %*d ", keys.length_pwd, file->pwd, keys.length_group, file->group, keys.length_size, (int)file->buf.st_size);
        ft_print_time(file->buf);
        ft_printf("%s", file->file);
	    if (file->target)
		    ft_printf(" -> %s", file->target);
	    ft_printf("\n");
    }
}

void    ft_print_list(t_files *files, t_keys keys)
{
    while (files)
    {
        if (*(files->file) != '.' || keys.all || (ft_strrchr(files->file, '/') && *(ft_strrchr(files->file, '/') + 1) != '.'))
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
    if (!in_the_first_time++)//Проблемы с выводом, как исправить?
        ft_print_only_file(files, keys);
    while (files)
    {
        if (S_ISDIR(files->buf.st_mode) && (*files->file != '.' || (keys.all && ((ft_strcmp(files->file, ".") && ft_strcmp(files->file, "..")) || !ft_strcmp(files->full_path, files->file))) || !ft_strcmp(files->full_path, files->file)))
        {
            total = -1;
            if (in_the_first_time || keys.recursive)
                ft_printf("%s: \n", files->full_path);
            opens_folder = ft_opendir(files, &keys, &total);
            if (keys.list && total > -1)
                ft_printf("total %d\n", total);
            ft_print_list(opens_folder, keys);
	        ft_initialize_length(&keys);
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