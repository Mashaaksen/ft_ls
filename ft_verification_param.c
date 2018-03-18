#include "ft_ls.h"

void    ft_file_search(char *param, t_ls *ls)
{
    int errnum;
    struct stat buf;
    errnum = lstat(param, &buf);
    if (errnum != 0)
        perror(param);
    else
        ls->files = ft_initialize_files(ls->files, buf, param, NULL, ls->keys);


}

void    ft_keys_search(char *param, t_ls *ls)
{
    int iter;

    iter = 1;
    while (param[iter])
    {
        if (param[iter] == 'l' || param[iter] == 'R' || param[iter] == 'a' || param[iter] == 'r' || param[iter] == 't')
        {
            if (param[iter] == 'l')
                ls->keys.list = 1;
            else if (param[iter] == 'R')
                ls->keys.recursive = 1;
            else if (param[iter] == 'a')
                ls->keys.all = 1;
            else if (param[iter] == 'r')
                ls->keys.revers = 1;
            else if (param[iter] == 't')
                ls->keys.time = 1;
            iter++;
        }
        else
            ft_error(ft_strjoin("Error keys", ""));
    }
}

void    ft_verification_param(int ac, char **av, t_ls *ls)
{
    int iter;

    iter = 1;
    while (iter < ac)
    {
        if (*(av[iter]) == '-' && ft_strlen(av[iter]) > 1)
            ft_keys_search(av[iter], ls);
        else
            ft_file_search(av[iter], ls);
        iter++;
    }
    if (!ls->files)
    {
        struct stat buf;
        lstat(".", &buf);
        ls->files = ft_initialize_files(ls->files, buf, ".", ".", ls->keys);
    }
}