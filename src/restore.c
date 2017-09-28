#include "ft_select.h"

void	ft_ti_norme(t_tc *tc)
{
	if (g_sig == SIGWINCH)
	{
		if (tc->stat)
			tputs(tc->cl, 0, term);
		else
		{
			tc->stat = 1;
			tputs(tc->ti, 0, term);
		}
	}
}

int		restore(struct termios backup, t_tc *tc)
{
	int	i;

	if (tc->stat == 1)
	{
		tputs(tc->te, 0, term);
		tc->stat = 0;
	}
	tputs(tc->cd, 0, term);
	tputs(tc->ve, 0, term);
	if (tcsetattr(0, TCSANOW, &backup) < 0)
		return (-1);
	if (g_sig == SIGTSTP || g_sig == SIGQUIT)
	{
		i = 0;
		while (i < 10000000)
			i++;
		signal(SIGTSTP, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ioctl(0, TIOCSTI, g_sig == SIGTSTP ? "\032" : "\034");
		init_sig();
	}
	return (0);
}
