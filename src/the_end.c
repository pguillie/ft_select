#include "ft_select.h"

void	the_end(char *av[], int status[])
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (status[i] & SELECT)
		{
			write(1, av[i], ft_strlen(av[i]));
			write(1, " ", 1);
		}
		i++;
	}
}
