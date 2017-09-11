#include "ft_select.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*pud;
	unsigned char	uc;

	pud = (unsigned char*)b;
	uc = (unsigned char)c;
	while (len--)
		pud[len] = uc;
	return (b);
}
