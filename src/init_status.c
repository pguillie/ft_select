#include "ft_select.h"

int		init_status(int status[], int ac)
{
	int		i;

	i = 0;
	while (i < ac)
		status[i++] = 0;
	status[i - 1] = END;
	status[0] = ac - 1;
	status[1] = CURSOR;
	return (0);
}
