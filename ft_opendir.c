#include "ft_ls.h"

/*
    Открыла папку с файлами, считала оттуда все файлы,
    получила buf stat-ом и отправила на инициализацию, всё,
    закрыла папку.
 */

t_files *ft_opendir(t_files *files, t_keys *keys, int *total)
{
    t_files *new_file;
    t_serv  serv;
    char *path;
	int errnum;

    new_file = NULL;
    path = NULL;
    serv.dir = opendir(files->full_path);//сделать проверку на NULL!!!
	if (!serv.dir)
		perror(ft_strjoin("ft_ls: ", files->file));
	else
	{
		while ((serv.read = readdir(serv.dir)))
        {
            path = ft_strjoin(ft_strjoin(files->full_path, "/"), serv.read->d_name);
            errnum = lstat(path, &serv.buf);
	        if (errnum)
		        perror(ft_strjoin("ft_ls: ", serv.read->d_name));
	        else
	        {
		        *total == -1 ? *total = 0 : 0;
		        if (keys->list && (*serv.read->d_name != '.' || keys->all))
			        *total = *total + serv.buf.st_blocks;
		        new_file = ft_initialize_files(new_file, serv.buf, serv.read->d_name, path, keys);
	        }
	        free(path);
        }
        closedir(serv.dir);
	}
    return (new_file);
}