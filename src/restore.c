#include "ft_select.h"

int		restore(struct termios backup, t_tc tc)
{
	int	i;

	i = 0;
	tputs(tc.cd, 0, termput);
	tputs(tc.ve, 0, termput);
	if (tcsetattr(0, TCSANOW, &backup) < 0)
		return (-1);
	if (g_sig == SIGTSTP || g_sig == SIGQUIT)
	{
		while (i < 100000)
			i++;
		signal(SIGTSTP, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ioctl(0, TIOCSTI, g_sig == SIGTSTP ? "\032" : "\034");
		init_sig();
	}
	return (0);
}
