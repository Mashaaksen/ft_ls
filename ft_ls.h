#ifndef FT_LS_H
#define FT_LS_H

#include "libft/libft.h"
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>
#include <sys/xattr.h>
#include <time.h>
#include <stdio.h>

typedef struct		s_key
{
	char 			s;
	struct s_key	*next;
}					t_key;

typedef struct		s_time
{
	int 			month;
	int 			day;
	int 			hour;
	int 			minute;
	int 			sec;
}					t_time;

typedef struct		s_name
{
	char			*time;
	char 			*name_gr;
	char 			*name_pw;
	off_t			size;
	nlink_t			link;
	t_time			time1;
	char 			tipe;
	char 			*mode;
	char			*str;
	struct s_name	*next;
}					t_name;

typedef struct		s_path
{
	char 			*str;
	struct s_path	*next;
	int 			ac;
}					t_path;

typedef struct		s_ls
{
	char 			*str;
	DIR				*dir;
	struct dirent	*entry;
	t_name			*names;
	struct stat		buff;
	struct passwd	*uid;
	struct group	*gid;
}					t_ls;

void				ft_keys(char **av, t_key **key, t_path **path, int *len);
void				ft_print_list(t_key *key, t_path *path);
void				ft_name(t_name **names, t_ls *ls);
void				ft_alpha_sort(t_name **name);
void				error_option(char c);
void				ordinary(t_key *key, t_path *path, int flag, int rec);
void				ft_time_sort(t_name **name);
void				ft_print(t_ls *ls, int i, t_key *key);
int					find_a(t_key *key);
void				add_path(char *str, t_path **path);

#endif
