/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <maksenov@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 17:17:00 by maksenov          #+#    #+#             */
/*   Updated: 2017/06/08 17:17:01 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# define PATH_LEN 256

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <dirent.h>

typedef struct		s_key
{
	char			s;
	struct s_key	*next;
}					t_key;

typedef struct		s_time
{
	int				month;
	int				day;
	int				hour;
	int				minute;
	int				sec;
}					t_time;

typedef struct		s_name
{
	char			*time;
	char			*name_gr;
	char			*name_pw;
	off_t			size;
	nlink_t			link;
	t_time			time1;
	char			*target;
	char			tipe;
	char			*mode;
	char			*str;
	struct s_name	*next;
}					t_name;

typedef struct		s_dir
{
	DIR				*dir;
	struct stat		buff;
	struct dirent	*entry;
}					t_dir;

typedef struct		s_path
{
	char			*road;
	char 			*name_file;
	struct s_path	*next;
}					t_path;

typedef struct		s_ls
{
	char 			*str;
	t_dir			dir;
	int 			dot;
	int 			rev;
	int 			total;
	int 			inscr;
	t_name			*names;
	struct stat		buff;
	struct passwd	*uid;
	struct group	*gid;
	int				max_size;
	int				max_link;
	int				max_name_gr;
	int				max_name_pw;
}					t_ls;

void				ft_keys(char **av, t_key **key, t_path **path, int *len);
void				ft_name(t_name **names, t_ls **ls);
void				ft_alpha_sort(t_name **name, int flag);
void				error_option(char c);
void				ordinary(t_key *key, t_path *path, int flag, int rec);
void				ft_time_sort(t_name **name, int flag);
void				ft_print_ls(t_ls *ls, int i, t_key *key);
int					find_a(t_key *key);
int					add_path(char *str, t_path **path, int flag);
int					find_r(t_key *key);
void				rostring(t_name **name);
int					open_read_dir(t_ls **ls, t_path *path);
int					find_time(t_key *key);
int					find_l(t_key *key);
void				find_tipe(char *p, mode_t mode);
void				find_mode(char **str, mode_t mode);
void				add_keys(t_key **key, char c);
void				check_keys(char *str, t_key **key);
void				initialization(t_name *name, t_name **tmp, t_name **p,
						t_name **r);
void				next_elem(t_name *r, int i, t_name **tmp, t_name **p);
void				add_tmp(t_name **name, t_name *p);
int					len_name(t_name *name);

#endif
