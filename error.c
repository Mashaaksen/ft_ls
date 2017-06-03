#include "ft_ls.h"

void		error_option(char c)
{
	ft_putstr("ft_ls: illegal option -- ");
	write(1, &c, 1);
	ft_putstr("\n");
	ft_putstr("usage: ls [-lRart] [file ...]");
	ft_putstr("\n");
	exit(0);
}
