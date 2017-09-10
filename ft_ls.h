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

typedef struct 		s_key
{
	int 			key_all;
	int 			key_list;
	int 			key_recurs;
	int 			key_rev;
	int 			key_time;
}					t_key;

typedef struct 		s_path
{
	char 			*av;
	char 			*road;
	char 			*file;
	struct stat		buff;
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

#endif
