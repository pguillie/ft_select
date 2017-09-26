#include "ft_select.h"

void	move(int status[], char move, int line)
{
	int	cur;
	int	tar;

	cur = 1;
	while (!(status[cur] & CURSOR))
		cur++;
	tar = cur;
	if (move & UP)
		tar = (cur == 1) ? status[0] : cur - 1;
	else if (move & DOWN)
		tar = (cur == status[0]) ? 1 : cur + 1;
	if (move & RIGHT)
		tar = (cur > status[0] - line) ? (cur % line) + 1 : cur + line;
	if (move & LEFT)
	{
		if (cur <= line)
			tar = status[0] + 1 - line + (
				(cur + line - 1) % (line + 1) + (cur + line - 1) / (line + 1)
				+ line - (status[0] + 1) % line) % line;
		else
			tar = cur - line;
	}
	status[cur] ^= CURSOR;
	status[tar] |= CURSOR;
}

int		delete(char *av[], int status[], t_tc tc)
{
	int	cur;
	int	i;

	tputs(tc.cd, 0, term);
	cur = 1;
	while (!(status[cur] & CURSOR))
		cur++;
	i = cur;
	while (av[i])
	{
		av[i] = av[i + 1];
		status[i] = status[i + 1];
		i++;
	}
	status[i - 2] = END;
	status[av[cur] ? cur : cur - 1] |= CURSOR;
	status[0] -= 1;
	return (av[1] ? 0 : 1);
}

void	selection(int status[])
{
	int	cur;

	cur = 1;
	while (!(status[cur] & CURSOR))
		cur++;
	status[cur] = ~(status[cur] ^ ~SELECT);
	if (status[cur] & FIND)
		tab(status);
	else
		move(status, DOWN, 0);
}
