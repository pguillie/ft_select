#include "ft_select.h"

static void	handler(int sig)
{
	g_sig = sig;
}

void		sig_tstp(void)
{
	struct sigaction	tstp;

	ft_memset(&tstp, 0, sizeof(tstp));
	tstp.sa_handler = SIG_DFL;
	sigaction(SIGTSTP, &tstp, 0);
	ioctl(0, TIOCSTI, "\032");
}

void		init_sig(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = handler;
	sigaction(SIGTERM, &act, 0);
	sigaction(SIGINT, &act, 0);
	sigaction(SIGQUIT, &act, 0);
	sigaction(SIGCONT, &act, 0);
	sigaction(SIGTSTP, &act, 0);
	sigaction(SIGWINCH, &act, 0);
}
