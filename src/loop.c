#include "ft_select.h"

static int	escape(char *av[], int status[], t_tc tc, int line)
{
	char	esc[8];
	int		i;
	int		ret;

	ft_memset(esc, 0, 8);
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
		ret = delete(av, status, tc);
	return (ret);
}

int			loop(char *av[], int status[], t_tc tc, int	 len)
{
	char	byte;
	int		ret;
	int		line;
	int		i;

	byte = 1;
	ret = 0;
	while (byte != '\n' && !ret)
	{
		if (byte)
		{
			line = display_string_array(av + 1, status + 1, tc, len);
			i = 0;
			while (i++ < line - 1)
				tputs(tc.up, 0, termput);
		}
		write(0, "\r", 1);
		byte = 0;
		if (read(0, &byte, 1) < 0)
			return (-1);
		if (byte == 27)
			ret = escape(av, status, tc, line);
		else if (byte == ' ')
			selection(status);
		else if (byte == 127)
			ret = delete(av, status, tc);
	}
	return (ret);
}
