#include "ft_select.h"

static int	escape(char *av[], int status[], t_tc *tc, int line)
{
	char	esc[8];
	int		i;
	int		ret;

	ft_memset(esc, 0, 8);
	ft_memset(tc->find, 0, 128);
	if (read(0, esc, 1) < 1 && errno != EINTR)
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

int			loop(char *av[], int status[], t_tc tc, int len)
{
	struct termios	backup;
	char			byte;
	int				ret;
	int				line;
	int				i;

	byte = 1;
	ret = 0;
	while (byte != '\n' && !ret)
	{
		if (g_sig == SIGCONT)
		{
			
		}
		if (g_sig == SIGTERM || g_sig == SIGINT || g_sig == SIGQUIT)
		{
			tputs(tc.cd, 0, termput);
			return (g_sig);
		}
		if (g_sig == SIGTSTP)
			return (g_sig);
		if (byte || g_sig == SIGWINCH || g_sig == SIGCONT)
		{
			g_sig = 0;
			tputs(tc.cd, 0, termput);
			line = display_string_array(av + 1, status + 1, tc, len);
			i = 0;
			while (i++ < line - 1)
				tputs(tc.up, 0, termput);
		}
		write(0, "\r", 1);
		byte = 0;
		if (read(0, &byte, 1) < 0 && errno != EINTR)
			return (-1);
		if (byte == 27)
			ret = escape(av, status, &tc, line);
		action(av, status, &tc, byte);
	}
	return (ret);
}
