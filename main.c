#include "ft_ls.h"

int 		find_recursion(t_key *key)
{
	while (key != NULL)
	{
		if (key->s == 'R')
			return (1);
		key = key->next;
	}
	return (0);
}


int 		main(int ac, char **av)
{
	t_key	*key;
	t_path	*path;
	int		len;

	key = NULL;
	ft_keys(av, &key, &path, &len);
	ordinary(key, path, len, find_recursion(key) == 1 ? 1 : 0);
	return(0);
}