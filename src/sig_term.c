#include "ft_select.h"

int		sig_term(t_tc tc)
{
	tputs(tc.cd, 0, termput);
	return (g_sig);
}
