#ifndef FT_LS_H
# define FT_LS_H

# define PATH_LEN 256

# include "libft/libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <dirent.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>

typedef struct			s_char_list
{
	char 				*av;
	char 				*tipe;
	char 				*mode;
	nlink_t				st_nlink;
	char				*pw_name;
	char				*gr_name;
	off_t				st_size;
	int 				year;
	char 				*str_month;
	int					day;
	int					hour;
	int					minute;
	char 				*file;
	char 				*target;
	struct s_char_list	*next;
}					t_char_list;

typedef struct		s_time
{
	int 			month_now;
	int 			year;
	char 			*str_month;
	int				day;
	int				hour;
	int				minute;
	long 			nansec;
	__darwin_time_t	tv_sec;
}					t_time;

typedef struct 		s_key
{
	int 			key_all;
	int 			key_group;
	int 			key_without_sort;
	int 			key_use_atime;
	int 			key_color;
	int 			key_list;
	int 			key_recurs;
	int 			key_rev;
	int 			key_time;
	int 			key_one;
	int 			file;
	int 			count;
	int 			count_all;
	int 			count_without_dot;
	int 			total;
	int				max_size;
	int				max_link;
	int				max_name_gr;
	int				max_name_pw;
	int 			max_len_mode;
	int 			max_len_name;
	int 			max_len_name_dot;
	int 			print_col;
	int 			print_line;
	unsigned short	*ws_col;
}					t_key;

typedef struct 		s_path
{
	char 			*av;
	char 			*road;
	char 			*file;
	t_time			time;
	struct stat		buff;
	char 			type;
	char 			*mode;
	char 			*target;
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
void		find_path(t_ls *ls, char **av);
void 		ft_ls(t_path *path, t_key keys, int flag, t_path *tmp);
void 		add_and_sort(t_key keys, t_path **path, t_path *tmp);
int			alpha(char *a, char *b);
int 		check_right_path(char *av, t_dir *inform, t_path **tmp, t_key key);
int			ft_time(t_time a, t_time b, char *path, char *tmp);
void		ft_find_time(t_time *tmp, struct stat buff, t_key key);
void 		add_list(t_path *path, t_key *keys, t_char_list **list, t_char_list *tmp);
void		print_tipe(mode_t mode, char *str);
void		print_mode(mode_t mode, char **str, char *path);
void 		print_file(t_path *path,t_key keys);
t_char_list *get_list(t_path *path, t_key *keys, int i, t_char_list *tmp);
void add_terget(const t_path *path, t_char_list **tmp);
void	new_ls(t_ls **ls);
void		forward_alpha(t_path **path, t_path *tmp, t_path *head);
void		back_alpha(t_path **path, t_path *tmp, t_path *head);
void		print_list(t_key keys, t_path *path, int dir);
int					read_all(t_path *path, t_path **tmp, t_key *key);
void create(t_path **tmp, t_key *key, t_dir inform, char *road);
void stat_create(t_key *key, t_path **p);


#endif
