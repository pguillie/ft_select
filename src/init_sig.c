#include "ft_select.h"

static void	handler(int sig)
{
	g_sig = sig;
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
