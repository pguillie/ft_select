#include "ft_select.h"

int		start_display(int status[], int last, int *dim, t_tc tc)
{
	int		cur;
	int		start;
	int		last_col;

	start = last;
	cur = 0;
	while (!(status[cur] & CURSOR))
		cur++;
	last_col = status[-1]
		- ((status[-1] % dim[1]) > 0 ? status[-1] % dim[1] : dim[1]);
	if (start && (status[-1] - start - 1) / dim[1] < dim[0] - 1)
		start -= dim[1];
	if (dim[0] == 1)
		start = cur / dim[1] * dim[1];
	else
	{
		if (cur < last + (dim[0] > 2 ? dim[1] - 1 : 0))
			start = cur / dim[1] * dim[1] - (cur >= dim[1] ? dim[1] : 0);
		else if (cur >= last + dim[0] * dim[1] - (dim[0] > 2 ? dim[1] : 0))
			start = cur + dim[1] - 1 - cur % dim[1] + 1 - dim[0] * dim[1]
				+ (cur < last_col ? dim[1] : 0);
	}
	if (start != last)
		tputs(tc.cd, 0, termput);
	return (start);
}
