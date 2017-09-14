#include "ft_select.h"

int		restore(struct termios backup, t_tc tc)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	tputs(tc.ve, 0, termput);
	tputs(tc.cd, 0, termput);
	if (tcsetattr(0, TCSANOW, &backup) < 0)
		return (-1);
	if (g_sig == SIGTSTP || g_sig == SIGQUIT)
	{
		act.sa_handler = SIG_DFL;
		sigaction(g_sig, &act, 0);
		ioctl(0, TIOCSTI, g_sig == SIGTSTP ? "\032" : "\034");
		init_sig();
	}
	return (0);
}
