#include "ft_select.h"

static int	found(char *str, char *find)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i + j] == find[j])
			j++;
		if (find[j] == '\0')
			return (1);
		i++;
	}
	return (0);
}

void		find(char *av[], int status[], char *find, char byte)
{
	int		i;
	int		cur;

	i = 0;
	while (find[i])
		i++;
	if (byte == 127)
		find[i ? i - 1 : 0] = '\0';
	else if (i < 128)
		find[i] = byte;
	i = 1;
	while (av[i])
	{
		status[i] &= ~FIND;
		if (find[0])
		{
			if (found(av[i], find))
				status[i] |= FIND;
		}
		if (status[i] & CURSOR)
			cur = i;
		i++;
	}
	if (find[0] && !(status[cur] & FIND))
		tab(status);
}
