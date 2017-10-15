/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maksenov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 15:46:22 by maksenov          #+#    #+#             */
/*   Updated: 2016/12/19 12:25:07 by maksenov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include "get_next_line.h"
# include <stdarg.h>
# include <stdint.h>

typedef	struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef struct		s_print
{
	int				mynus;
	int				plus;
	int				null;
	int				space;
	int				hash;
	int				weidth;
	int				accuracy;
	char			*size;
	int				proc;
	char			type;
	int				cost;
	char			*p;
	int				fm;
	void			*i;
}					t_print;

int					ft_count_words(char const *s, char c);
int					ft_isalpha(int c);
int					ft_isprint(int c);
char				*ft_strcpy(char *s2, const char *s1);
int					ft_isdigit(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
void				ft_bzero(void *str, size_t num);
void				*ft_memmove(void *dst, const void *src, size_t c);
size_t				ft_strlen(const char *s);
char				*ft_strstr(const char *str1, const char *str2);
char				*ft_strrchr(const char *str, int c);
char				*ft_strncpy(char *dest, const char *src, size_t len);
char				*ft_strnstr(const char *str1, const char *str2, size_t len);
int					ft_strncmp(const char *str1, const char *str2, size_t num);
char				*ft_strncat(char *dest, const char *app, size_t len);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strchr(const char *s, int c);
char				*ft_strcat(char *dest, const char *app);
void				*ft_memcpy(void *dst, const void *src, size_t n);
int					ft_memcmp(const void *src, const void *dst, size_t n);
void				*ft_memchr(const void *str, int c, size_t n);
int					ft_isascii(int c);
int					ft_isalnum(int c);
int					ft_atoi(const char *str);
void				*ft_memset(void *str, int c, size_t len);
char				*ft_strdup(char const *str);
void				*ft_memccpy(void *dst, const void *src, int c, size_t n);
size_t				ft_strlcat(char *dest, const char *sorc, size_t size);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
void				ft_putchar(char c);
void				ft_putstr(char const *str);
void				ft_memdel(void **ap);
char				*ft_strnew(size_t size);
void				*ft_memalloc(size_t size);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char const *s, int fd);
void				ft_strdel(char **as);
void				ft_strclr(char *s);
void				ft_striter(char *s, void (*f)(char *));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strmap(char const *s, char (*f)(char));
char				*ft_strmapi(char const *s, char(*f)(unsigned int, char));
int					ft_strequ(char const *s1, char const *s2);
int					ft_strnequ(char const *s1, char const *s2, size_t n);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s);
char				**ft_strsplit(char const *s, char c);
void				ft_putendl(char const *s);
void				ft_putnbr(int n);
void				ft_putendl_fd(char const *s, int fd);
void				ft_putnbr_fd(int n, int fd);
t_list				*ft_lstnew(void const *content, size_t content_size);
void				ft_lstadd(t_list **alst, t_list *new);
void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));
void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
char				*ft_itoa_base(unsigned long long value, char c);
t_print				*check_accuracy(const char **str,
									   va_list ap, t_print *print);
int					ft_printf(const char *format, ...);
int					fill(const char *str, t_print *print, va_list ap);
t_print				*check_width(const char **str,
									va_list ap, t_print *print);
t_print				*check_flag(const char **str, t_print *print);
t_print				*check_size(const char **str, t_print *print);
int					find_spec(char *str);
t_print				*check_type(const char **str, t_print *print);
void				full(t_print **print);
int					ft_print(t_print *print, va_list ap);
char				*ft_itoa_long(long long n);
t_print				*change(t_print *print);
int					check_all(t_print *print, char **str);
char				*proc(const char *str, t_print *print,
						  va_list ap, int *ret);
char				*accuracy(t_print *print, char *str);
char				*flag_weidth(t_print *print, char *str);
char				*find_str(t_print *print, va_list ap);
long long			ft_int_min(long long n);
int					ft_len_int(long long n);
char				*ft_wchar(wchar_t *str, t_print *print);
t_print				*my_print(t_print *print, char *str);
char				*ft_strndup(char *sorc, size_t n);

#endif
