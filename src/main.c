#include "ft_select.h"

int		main(int ac, char *av[])
{
	struct termios		backup;
	t_tc				tc;
	int					status[ac];
	int					ret;
	size_t				len;

	sig_init();
	if ((ret = 1) && ac > 1)
	{
		if (termcaps(&tc))
			return (1);
		if (raw(&backup) < 0)
			return (1);
		tputs(tc.vi, 0, termput);
		init_status(status, ac);
		len = init_len(av + 1);
		ret = loop(av, status, tc, len);
		tputs(tc.ve, 0, termput);
		tputs(tc.cd, 0, termput);
		if (tcsetattr(0, TCSANOW, &backup) < 0)
			return (-1);
		if (ret == 0)
			the_end(av, status);
	}
	return (ret);
}
