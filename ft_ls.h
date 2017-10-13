#ifndef FT_LS_H
# define FT_LS_H

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

typedef struct		s_time
{
	char 			*str_month;
	int				month;
	int				day;
	int				hour;
	int				minute;
	int				sec;
}					t_time;

typedef struct 		s_key
{
	int 			key_all;
	int 			key_list;
	int 			key_recurs;
	int 			key_rev;
	int 			key_time;
	int 			file;
	int 			count;
	int 			total;
}					t_key;

typedef struct 		s_path
{
	char 			*av;
	char 			*road;
	char 			*file;
	t_time			time;
	struct stat		buff;
	char 			type;
	struct passwd	*uid;
	struct group	*gid;
	struct s_path	*next;
}					t_path;

typedef struct 		s_dir
{
	DIR				*dir;
	struct dirent	*entry;
}					t_dir;

typedef	struct 		s_ls
{
	t_key			keys;
	t_path			*path;
	t_dir			inform;
}					t_ls;

void 		find_keys(t_ls *ls, char ***av);
void 		find_path(t_ls *ls, char **av);
void 		ft_ls(t_path *path, t_key keys, int flag);
void 		add_and_sort(t_key keys, t_path **path, t_path *tmp);
int			alpha(char *a, char *b);
void 		check_right_path(char *av, t_dir *inform, t_path **tmp, t_key *key);
int			ft_time(t_time a, t_time b);
void		ft_find_time(t_time *tmp, struct stat buff);
int			find_month(char *str, int i);

#endif
