#include "ft_select.h"

int		start_display(int status[], int last, int *dim, t_tc tc)
{
	int		cur;
	int		start;
	int		end;

	start = last;
	cur = 0;
	while (!(status[cur] & CURSOR))
		cur++;
	end = cur;
	while (!(status[end] & END))
		end++;
	if (start && (end - start) / dim[1] < dim[0] - 1)
		start -= dim[1];
	if (cur < last)
		start = cur / dim[1] * dim[1];
	else if (cur >= last + dim[0] * dim[1])
		start = cur + dim[1] - 1 - cur % dim[1] + 1 - dim[0] * dim[1];
	dprintf(5, "cur: %d -- start: %d\n", cur, start);
	if (start != last)
		tputs(tc.cd, 0, termput);
	return (start);
}
