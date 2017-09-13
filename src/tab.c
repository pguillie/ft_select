#include "ft_select.h"

void	tab(int status[])
{
	int	cur;
	int	next;

	cur = 1;
	while (!(status[cur] & CURSOR))
		cur++;
	next = cur + 1;
	while (!(status[next] & FIND))
	{
		if (next >= status[0])
			next = 1;
		if (next == cur)
			break ;
		next++;
	}
	status[cur] ^= CURSOR;
	status[next] |= CURSOR;
}
