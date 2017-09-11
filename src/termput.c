#include "ft_select.h"

int		termput(int n)
{
	char	c;

	c = n;
	write(0, &c, 1);
	return (n);
}
