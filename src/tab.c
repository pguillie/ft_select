#include "ft_select.h"

void	tab(int status[])
{
	int	cur;
	int	next;

	cur = 1;
	while (!(status[cur] & CURSOR))
		cur++;
	next = (cur == status[0]) ? 1 : cur + 1;
	while (!(status[next] & FIND) && next != cur)
	{
		if (next == status[0])
			next = 1;
		else
			next += 1;
	}
	status[cur] ^= CURSOR;
	status[next] |= CURSOR;
}
