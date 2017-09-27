#include "ft_select.h"

static int	escape(char *av[], int status[], t_tc *tc, int line)
{
	char	esc[8];
	int		i;
	int		ret;

	ft_memset(esc, 0, 8);
	ft_memset(tc->find, 0, 128);
	if (read(0, esc, 1) < 1)
		return (1);
	i = 1;
	ret = 0;
	while (esc[0] == '[' && i < 7)
	{
		read(0, esc + i, 1);
		if (esc[i] >= '@' && esc[i] <= '~')
			break ;
		esc[++i] = 0;
	}
	if (esc[1] >= 'A' && esc[1] <= 'D' && !esc[2])
		move(status, 1 << ((esc[1] ^ 64) - 1), line);
	else if (esc[1] == '3' && esc[2] == '~' && !esc[3])
		ret = delete(av, status, *tc);
	return (ret);
}

static void	action(char *av[], int status[], t_tc *tc, int byte)
{
	if (byte == ' ')
		selection(status);
	else if (byte == '\t')
		tab(status);
	else if (byte > ' ' && byte <= 127)
		find(av, status, tc->find, byte);
}

static int	sigloop(struct termios *backup, t_tc *tc)
{
	int		ret;

	ret = 0;
	if ((g_sig == SIGTSTP || g_sig == SIGQUIT) && restore(*backup, tc) < 0)
		ret = -1;
	else if (g_sig == SIGTERM || g_sig == SIGINT)
		ret = g_sig;
	else if (g_sig == SIGCONT)
	{
		if (raw(backup) < 0)
			ret = -1;
		else
		{
			tputs(tc->vi, 0, term);
			ret = 0;
		}
	}
	return (ret);
}

static void	loopup(int line, t_tc tc)
{
	int		i;

	i = 0;
	if (g_sig != SIGTSTP)
		g_sig = 0;
	while (i++ < line - 1)
		tputs(tc.up, 0, term);
	write(0, "\r", 1);
}

int			loop(char *av[], int status[], t_tc *tc, int len)
{
	struct termios	backup;
	char			byte;
	int				ret;
	int				line;

	byte = 1;
	ret = 0;
	while (byte != '\n' && !ret)
	{
		if ((ret = sigloop(&backup, tc)) < 0)
			return (-1);
		if (byte || g_sig == SIGWINCH || g_sig == SIGCONT)
		{
			tputs(tc->cd, 0, term);
			if ((line = display_string_array(av + 1, status + 1, tc, len)) < 0)
				g_sig = SIGTSTP;
			loopup(line, *tc);
		}
		if (!(byte = 0) && read(0, &byte, 1) < 0)
			return (-1);
		if (byte == 27)
			ret = escape(av, status, tc, line);
		action(av, status, tc, byte);
	}
	return (restore(backup, tc) < 0 ? -1 : ret);
}
