#ifndef FT_LS_H
# define FT_LS_H

# define PATH_LEN 256

# define mask_l 1
# define mask_r 2
# define mask_a 4
# define mask_R 8
# define mask_t 16

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <stdio.h>
# include <errno.h>
# include <sys/acl.h>

typedef	struct		s_keys
{
	int             flags;
	size_t             length_pwd;
	size_t             length_group;
	size_t             length_link;
	size_t             length_size;
	size_t          length_permission;
}					t_keys;

typedef	struct		s_files
{
    char            *group;
    char            *pwd;
    char            *file;
    char            *full_path;
	char            *target;
	char            *permission;
    struct stat     buf;
    struct s_files  *next;
}					t_files;

typedef	struct		s_ls
{
    t_keys          keys;
    t_files         *files;
}					t_ls;

typedef struct      s_serv
{
    DIR             *dir;
    struct dirent   *read;
    struct stat     buf;
    struct group    *group;
    struct passwd   *passwd;
}                   t_serv;

typedef int (*ft_compare_type)(t_files *curr_file, t_files *new_file);

void    ft_verification_param(int ac, char **av, t_ls *ls);
void    ft_initialize_ls(t_ls *ls);
void    ft_error(char *str);
t_files *    ft_initialize_files(t_files *files, struct stat buf, char *name_filee, char *full_path, t_keys *keys);
t_files *    ft_insert_files(t_files *files, t_files *new_files, t_keys keys);
t_files *ft_opendir(t_files *files, t_keys *keys, int *total);
void    ft_initialize_length(t_keys *keys);
void            ft_free_t_files(t_files **files);

#endif