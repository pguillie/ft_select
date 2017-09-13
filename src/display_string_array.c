#include "ft_select.h"

static int	appearance(char *array, int status, t_tc tc, int len)
{
	char	space[1024];

	ft_memset(space, ' ', 1024);
	len -= 1;
	if (status & CURSOR)
		tputs(tc.us, 0, termput);
	if (status & SELECT)
		tputs(tc.mr, 0, termput);
	if (tc.find[0])
		find(array, tc.find, status);
	else
		color(array);
	write(0, array, ft_strlen(array));
	tputs(tc.ue, 0, termput);
	write(0, space, len - (int)ft_strlen(array));
	tputs(tc.me, 0, termput);
	return (len - (int)ft_strlen(array));
}

static int	display_simple(char *array[], int status[], t_tc tc, int len)
{
	int		size;
/////////
	size = 0;
	while (array[size])
	{
		appearance(array[size], status[size], tc, len);
		write(0, "\n", 1);
		size++;
	}
	return (size);
}

static void	display_complex(char *array[], int dim[], int status[], t_tc tc)
{
	char			space[1024];
	int				i[3];
	int				col;
	int				mr;

	ft_memset(i, 0, 3 * sizeof(int));
	ft_memset(space, ' ', 1024);
	col = 0;
	while (i[0] < dim[2])
	{
		mr = 0;
		if (!(status[i[1]] & CURSOR)
				&& ((i[0] == 0 && status[i[0] - 1] != status[i[0] - dim[5] - 1])
				|| (i[0] == (dim[2] - 1) && !(status[i[0]] & END))))
			mr = appearance("...", 0, tc, dim[3] + 1);
		else
			mr = appearance(array[i[1]], status[i[1]], tc, dim[3]);
		if (col++ < dim[0] && i[1] + dim[4] < dim[2])
		{
			write(0, space, dim[3] - ft_strlen(array[i[1]]) - mr);
			i[1] += dim[4];
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

int			display_string_array(char *array[], int status[], t_tc tc, int len)
{
	struct winsize	w;
	int				dim[6];
	static int		start = 0;

	if (!array)
		return (0);
	if (ioctl(0, TIOCGWINSZ, &w) < 0)
		return (display_simple(array, status, tc, len));
	dim[2] = 0;
	dim[3] = len;
	while (array[dim[2]])
		dim[2]++;
	dim[1] = w.ws_col / dim[3] ? (dim[2] - 1) / (w.ws_col / dim[3]) + 1
		: dim[2];
	dim[0] = (dim[2] - 1) / dim[1] + 1;
	if (dim[1] > w.ws_row - 1)
	{
		dim[1] = w.ws_row - 1;
		dim[2] = dim[1] * dim[0];
		dim[0] = (dim[2] - 1) / dim[1] + 1;
	}
	dprintf(5, "dim: %d\n", dim[1]);//
	start = start_display(status, start, dim, tc);
	dim[2] = 0;
	while (array[start + dim[2]] && dim[2] < dim[1] * dim[0])
		dim[2]++;
	dim[4] = ((start ? dim[0] * dim[1] : dim[2]) - 1) / dim[0] + 1;
	dim[5] = start;
	display_complex(array + start, dim, status + start, tc);
	return (dim[1]);
}
