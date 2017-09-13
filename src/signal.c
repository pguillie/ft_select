#include "ft_select.h"

static void catch(int signal)
{
	dprintf(5,"signal: %d\n", signal);
	g_sig = signal;
}

void		sig_init(void)
{	
	struct sigaction	sig;

	sig.sa_handler = catch;
	sig.sa_flags = 0;
	sigaction(SIGINT, &sig,0);
	sigaction(SIGQUIT, &sig,0);
	sigaction(SIGCONT, &sig,0);
	sigaction(SIGWINCH, &sig,0);
	sigaction(SIGTSTP, &sig,0);
}

int		sig_action(void)
{
	int		i;

	i = g_sig;
	if (i == SIGINT)
		return (1);
	if (i == SIGWINCH)
		return (SIGWINCH);
	g_sig = 0;
	return (0);
}
