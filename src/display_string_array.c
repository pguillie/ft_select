#include "ft_select.h"

static void	appearance(char *array, int status, t_tc tc)
{
	if (status & CURSOR)
		tputs(tc.us, 0, termput);
	if (status & SELECT)
		tputs(tc.mr, 0, termput);
	write(0, array, ft_strlen(array));
	tputs(tc.ue, 0, termput);
	tputs(tc.me, 0, termput);
}

static int	display_simple(char *array[], int status[], t_tc tc)
{
	size_t	size;

	size = 0;
	while (array[size])
	{
		appearance(array[size], status[size], tc);
		write(0, "\n", 1);
		size++;
	}
	return (size);
}

static void	display_complex(char *array[], size_t dim[], int status[], t_tc tc)
{
	char			space[1024];
	size_t			i[3];
	size_t			col;

	ft_memset(i, 0, 3 * sizeof(size_t));
	ft_memset(space, ' ', 1024);
	col = 0;
	while (i[0] < dim[2])
	{
		appearance(array[i[1]], status[i[1]], tc);
		if (col++ < dim[0] && i[1] + (dim[2] - 1) / dim[0] + 1 < dim[2])
		{
			write(0, space, dim[3] - ft_strlen(array[i[1]]));
			i[1] += (dim[2] - 1) / dim[0] + 1;
		}
		else if (i[0] != dim[2] - 1)
		{
			write(0, "\r\n", 2);
			i[1] = ++i[2];
			col = 1;
		}
		i[0]++;
	}
}

int			display_string_array(char *array[], int status[], t_tc tc)
{
	struct winsize	w;
	size_t			dim[4];

	if (!array)
		return (0);
	if (ioctl(0, TIOCGWINSZ, &w) < 0)
		return (display_simple(array, status, tc));
	dim[2] = 0;
	dim[3] = 1;
	while (array[dim[2]])
	{
		if (ft_strlen(array[dim[2]]) + 1 > dim[3])
			dim[3] = ft_strlen(array[dim[2]]) + 1;
		dim[2]++;
	}
	dim[1] = w.ws_col / dim[3] ? (dim[2] - 1) / (w.ws_col / dim[3]) + 1
		: dim[2];
	dim[0] = (dim[2] - 1) / dim[1] + 1;
	display_complex(array, dim, status, tc);
	return (dim[1] - 1);
}
