/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialization.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 18:28:12 by maksenov          #+#    #+#             */
/*   Updated: 2018/03/23 18:28:12 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ft_initialize_length(t_keys *keys)
{
	keys->length_group = 0;
	keys->length_pwd = 0;
	keys->length_link = 0;
	keys->length_size = 0;
}

void		ft_initialize_ls(t_ls *ls)
{
	ls->keys.flags = 0;
	ft_initialize_length(&ls->keys);
	ls->files = NULL;
}

char		*ft_add_terget(char *path)
{
	ssize_t	k;
	char	link_name[PATH_LEN];
	char	*target;

	k = readlink(path, link_name, PATH_LEN);
	if (k >= PATH_LEN)
		target = ft_strdup("Wrong: link filename too long!");
	else
	{
		if (k == -1)
			target = ft_strdup("invalid symbolic link!");
		else
		{
			link_name[k] = '\0';
			target = ft_strdup(link_name);
		}
	}
	return (target);
}

void    ft_get_xattr(char **permissions, char *path)
{
	acl_t acl;
	acl_entry_t obj;
	ssize_t xattr;

	acl = acl_get_link_np(path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &obj) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		(*permissions)[9] = '@';
	else if (acl != NULL)
		(*permissions)[9] = '+';
	else
		(*permissions)[9] = ' ';
	acl_free(acl);
	acl = NULL;
}

char        *ft_get_permission(struct stat buf, char *full_path)
{
	char    *permission;
	int     i;
	char    *base;

	permission = ft_memalloc(sizeof(char) * 11);
	i = -1;
	base = "xwrxwrxwr";
	while (++i <= 8)
	{
		if (buf.st_mode & (1 << i))
			permission[8-i] = base[i];
		else
			permission[8-i] = '-';
	}
	if (buf.st_mode & S_ISUID)
		permission[2] = (char) ((buf.st_mode & S_IXUSR) ? 's' : 'S');
	else if (buf.st_mode & S_ISGID)
		permission[5] = (char) ((buf.st_mode & S_IXGRP) ? 's' : 'l');
	else if (buf.st_mode & S_ISVTX)
		permission[8] = (char) ((buf.st_mode & S_IXOTH) ? 't' : 'T');
	ft_get_xattr(&permission, full_path);
	return (permission);
}

t_files		*ft_initialize_files(t_files *files, struct stat buf,
			char *name_file, char *full_path, t_keys *keys)
{
	t_files	*new_files;
	t_serv	serv;
	size_t	len;

	new_files = (t_files *)malloc(sizeof(t_files));
	new_files->buf = buf;
	new_files->file = name_file ? ft_strdup(name_file) : NULL;
	new_files->full_path = full_path ? ft_strdup(full_path) :
			ft_strdup(name_file);
	if ((keys->flags & mask_l) && (*name_file != '.' || (keys->flags & mask_a) ||
			!ft_strcmp(name_file, full_path)))
	{
		serv.group = getgrgid(buf.st_gid);
		serv.passwd = getpwuid(buf.st_uid);
		new_files->permission = ft_get_permission(buf, new_files->full_path);
		new_files->group = ft_strdup(serv.group->gr_name);
		new_files->pwd = ft_strdup(serv.passwd->pw_name);
		len = ft_strlen(new_files->pwd);
		if (keys->length_pwd < len)
			keys->length_pwd = len;
		len = ft_strlen(new_files->group);
		if (keys->length_group < len)
			keys->length_group = len;
		len = (size_t)size_v(buf.st_nlink, 10);
		if (keys->length_link < len)
			keys->length_link = len;
		len = (size_t)size_v((unsigned long long int)buf.st_size, 10);
		if (keys->length_size < len)
			keys->length_size = len;
		if (S_ISLNK(buf.st_mode))
			new_files->target = ft_add_terget(full_path);
		else
			new_files->target = NULL;
	}
	else
	{
		new_files->group = NULL;
		new_files->pwd = NULL;
		new_files->target = NULL;
		new_files->permission = NULL;
	}
	new_files->next = NULL;
	files = ft_insert_files(files, new_files, *keys);
	return (files);
}
