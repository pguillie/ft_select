#include "ft_select.h"

int		main(int ac, char *av[])
{
	struct termios	backup;
	t_tc			tc;
	int				status[ac];
	int				ret;

	if (ac > 1)
	{
		if (termcaps(&tc))
			return (1);
		if (raw(&backup) < 0)
			return (1);
		tputs(tc.vi, 0, termput);
		init_status(status, ac);
		ret = loop(av, status, tc);
		tputs(tc.ve, 0, termput);
		tputs(tc.cd, 0, termput);
		if (tcsetattr(0, TCSANOW, &backup) < 0)
			return (-1);
	}
	the_end(av, status);
	return (0);
}
