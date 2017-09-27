#include "ft_select.h"

int		main(int ac, char *av[])
{
	t_tc				tc;
	int					status[ac];
	int					ret;
	size_t				len;

	init_sig();
	if ((ret = 1) && ac > 1)
	{
		if (termcaps(&tc))
		{
			write(2, "Termcaps not available :(\n", 26);
			return (1);
		}
		init_status(status, ac);
		len = init_len(av + 1);
		g_sig = SIGCONT;
		ret = loop(av, status, tc, len);
		tputs(tc.te, 0, term);
		if (ret == 0)
			the_end(av, status);
	}
	return (ret);
}
