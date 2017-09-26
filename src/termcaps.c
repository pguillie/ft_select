#include "ft_select.h"

static int	init_tc(t_tc *s, char **stc, char *tc)
{
	if (!(*stc = tgetstr(tc, (char**)&(s->buff))))
		return (1);
	return (0);
}

int			termcaps(t_tc *init)
{
	char	*termtype;
	int		success;

	if (!(termtype = getenv("TERM")))
		return (1);
	success = tgetent(init->data, termtype);
	if (success <= 0)
		return (1);
	ft_memset(init->buff, 0, 2048);
	if (init_tc(init, &init->cd, "cd")
			|| init_tc(init, &init->me, "me")
			|| init_tc(init, &init->mr, "mr")
			|| init_tc(init, &init->ue, "ue")
			|| init_tc(init, &init->up, "up")
			|| init_tc(init, &init->us, "us")
			|| init_tc(init, &init->ve, "ve")
			|| init_tc(init, &init->ti, "ti")
			|| init_tc(init, &init->te, "te")
			|| init_tc(init, &init->vi, "vi"))
		return (1);
	return (0);
}
