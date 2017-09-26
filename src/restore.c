#include "ft_select.h"

int		restore(struct termios backup, t_tc tc)
{
	int	i;

	tputs(tc.cd, 0, term);
	tputs(tc.ve, 0, term);
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
