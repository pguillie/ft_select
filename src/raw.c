#include "ft_select.h"

int		raw(struct termios *get)
{
	struct termios	set;

	if (tcgetattr(0, get) < 0)
		return (-1);
	set = *get;
	set.c_lflag &= ~(ECHO | ICANON);
	set.c_cc[VTIME] = 1;
	set.c_cc[VMIN] = 0;
	if (tcsetattr(0, TCSANOW, &set) < 0)
		return (-1);
	return (0);
}
