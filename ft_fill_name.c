#include <dirent.h>
#include "ft_ls.h"

void		find_mode(char **str, mode_t mode)
{
	*str = ft_strdup("");
	*str = ft_strjoin(*str, (mode & S_IRUSR) ? "r" : "-");
	*str = ft_strjoin(*str, (mode & S_IWUSR) ? "w" : "-");
	*str = ft_strjoin(*str, (mode & S_IXUSR) ? "x" : "-");
	*str = ft_strjoin(*str, (mode & S_IRGRP) ? "r" : "-");
	*str = ft_strjoin(*str, (mode & S_IWGRP) ? "w" : "-");
	*str = ft_strjoin(*str, (mode & S_IXGRP) ? "x" : "-");
	*str = ft_strjoin(*str, (mode & S_IROTH) ? "r" : "-");
	*str = ft_strjoin(*str, (mode & S_IWOTH) ? "w" : "-");
	*str = ft_strjoin(*str, (mode & S_IXOTH) ? "x" : "-");
}

void		find_tipe(char *p, mode_t mode)
{
	if (S_ISBLK(mode))
		*p = 'b';
	else if (S_ISCHR(mode))
		*p = 'c';
	else if (S_ISDIR(mode))
		*p = 'd';
	else if (S_ISREG(mode))
		*p = '-';
	else if (S_ISFIFO(mode))
		*p = 'f';
	else if (S_ISLNK(mode))
		*p = 'l';
	else if (S_ISSOCK(mode))
		*p = 's';
	else
		*p = '?';
}

int 		find_month(char *str, int i)
{
	if (i++ && !ft_strcmp(str, "Jan"))
		return(i);
	if (i++ && !ft_strcmp(str, "Feb"))
		return(i);
	if (i++ && !ft_strcmp(str, "Mar"))
		return(i);
	if (i++ && !ft_strcmp(str, "Apr"))
		return(i);
	if (i++ && !ft_strcmp(str, "May"))
		return(i);
	if (i++ && !ft_strcmp(str, "Jun"))
		return(i);
	if (i++ && !ft_strcmp(str, "Jul"))
		return(i);
	if (i++ && !ft_strcmp(str, "Aug"))
		return(i);
	if (i++ && !ft_strcmp(str, "Sep"))
		return(i);
	if (i++ && !ft_strcmp(str, "Oct"))
		return(i);
	if (i++ && !ft_strcmp(str, "Nov"))
		return(i);
	if (i++ && !ft_strcmp(str, "Dec"))
		return(i);
	return(i);
}

void 		ft_find_time(t_name **p, t_ls *ls)
{
	char 	**a;
	char 	**b;

	(*p)->time = ctime(&ls->buff.st_mtimespec.tv_sec);
	a = ft_strsplit((*p)->time, ' ');
	(*p)->time1.month = find_month(a[1], 0);
	(*p)->time1.day = ft_atoi(a[2]);
	b = ft_strsplit(a[3], ':');
	(*p)->time = a[1];
	(*p)->time1.hour = ft_atoi(b[0]);
	(*p)->time1.minute = ft_atoi(b[1]);
	(*p)->time1.sec = ft_atoi(b[2]);
}

void		ft_name(t_name **names, t_ls *ls)
{
	t_name	*tmp;
	t_name	*p;

	p  = (t_name *)malloc(sizeof(t_name));
	p->str = ft_strdup(ls->entry->d_name);
	ls->uid = getpwuid(ls->buff.st_uid);
	ls->gid = getgrgid(ls->buff.st_gid);
	p->name_pw = ft_strdup(ls->uid->pw_name);
	p->name_gr = ft_strdup(ls->gid->gr_name);
	ft_find_time(&p, ls);
	p->size = ls->buff.st_size;
	p->link = ls->buff.st_nlink;
	find_tipe(&p->tipe, ls->buff.st_mode);
	find_mode(&p->mode, ls->buff.st_mode);
	p->next = NULL;
	if (*names == NULL)
		*names = p;
	else
	{
		tmp = *names;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = p;
	}
}