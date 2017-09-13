#include "ft_select.h"

void	find(char *str, char *pattern, int status)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == pattern[j])
			j++;
		if (pattern[j] == '\0')
			break ;
		i++;
	}
	if (str[i])
		write(1, status & SELECT ? "\e[32m" : "\e[31m" , 5);
}
