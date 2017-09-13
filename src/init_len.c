#include "ft_select.h"

int			init_len(char *av[])
{
	int		len;
	int		i;

	i = 0;
	len = 3;
	while (av[i])
	{
		if ((int)ft_strlen(av[i]) + 1 > len)
			len = ft_strlen(av[i]) + 1;
		i++;
	}
	return (len);
}
