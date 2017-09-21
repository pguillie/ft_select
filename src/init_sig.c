#include "ft_select.h"

static void	handler(int sig)
{
	if (sig == SIGFPE || sig == SIGILL || sig == SIGSEGV || sig == SIGBUS
			|| sig == SIGABRT || sig == SIGIOT || sig == SIGTRAP
			|| sig == SIGEMT || sig == SIGSYS || sig == SIGHUP || sig == SIGALRM
			|| sig == SIGVTALRM || sig == SIGPROF || sig == SIGSYS
			|| sig == SIGTTIN || sig == SIGTTOU || sig == SIGPIPE
			|| sig == SIGXCPU || sig == SIGXFSZ || sig == SIGUSR1
			|| sig == SIGUSR2)
		g_sig = SIGTERM;
	else
		g_sig = sig;
}

static void	init_sig_norminette(void)
{
	signal(SIGIO, SIG_IGN);
	signal(SIGURG, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);
	signal(SIGCONT, handler);
	signal(SIGTSTP, handler);
	signal(SIGTTIN, handler);
	signal(SIGTTOU, handler);
	signal(SIGPIPE, handler);
	signal(SIGXCPU, handler);
	signal(SIGXFSZ, handler);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	signal(SIGWINCH, handler);
	signal(SIGINFO, SIG_IGN);
}

void		init_sig(void)
{
	signal(SIGFPE, handler);
	signal(SIGILL, handler);
	signal(SIGSEGV, handler);
	signal(SIGBUS, handler);
	signal(SIGABRT, handler);
	signal(SIGTRAP, handler);
	signal(SIGEMT, handler);
	signal(SIGTERM, handler);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGHUP, handler);
	signal(SIGALRM, handler);
	signal(SIGVTALRM, handler);
	signal(SIGPROF, handler);
	signal(SIGSYS, handler);
	init_sig_norminette();
}
