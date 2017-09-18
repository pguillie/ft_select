#include "ft_select.h"

static int	appearance(char *array, int status, t_tc tc, int len)
{
	char	space[1024];
	int		l;

	ft_memset(space, ' ', 1024);
	len -= 1;
	l = ft_strlen(array);
	if (status & CURSOR)
		write(0, "\e[3;4m", 6);
	if (status & SELECT)
		tputs(tc.mr, 0, termput);
	if (tc.find[0])
	{
		if (status & FIND)
			write(0, (status & SELECT) ? "\e[32;40m" : "\e[43;30m", 8);
	}
	else
		color(array);
	write(0, array, len < l ? len : l);
	tputs(tc.ue, 0, termput);
	write(0, space, len < l ? 0 : len - l);
	tputs(tc.me, 0, termput);
	return (len < l ? 0 : len - l);
}

static void	disp_write(char *str, int dim[], int i[], int mr)
{
	char		space[1024];

	ft_memset(space, ' ', 1024);
	if (i[3]++ < dim[0] && i[1] + dim[4] < dim[2])
	{
		write(0, space, dim[3] - ft_strlen(str) - mr);
		i[1] += dim[4];
	}
	else if (i[0] != dim[2] - 1)
	{
		write(0, "\r\n", 2);
		i[1] = ++i[2];
		i[3] = 1;
	}
}

static int	display_complex(char *array[], int dim[], int status[], t_tc tc)
{
	int				i[4];
	int				mr;

	ft_memset(i, 0, 4 * sizeof(int));
	while (i[0] < dim[2])
	{
		mr = 0;
		if (!(status[i[1]] & CURSOR)
				&& ((i[0] == 0 && status[i[0] - 1] != status[i[0] - dim[5] - 1])
				|| (i[0] == (dim[2] - 1) && !(status[i[0]] & END))))
			mr = appearance("...", 0, tc, dim[3] + 1);
		else
			mr = appearance(array[i[1]], status[i[1]], tc, dim[3]);
		disp_write(array[i[1]], dim, i, mr);
		i[0]++;
	}
	return (i[2] + 1);
}

static void	disp_norminette(int dim[], int row)
{
	dim[1] = row - 1;
	dim[2] = dim[1] * dim[0];
	dim[0] = (dim[2] - 1) / dim[1] + 1;
}

int			display_string_array(char *array[], int status[], t_tc tc, int len)
{
	struct winsize	w;
	int				dim[6];
	static int		start = 0;

	if (!array)
		return (0);
	if (ioctl(0, TIOCGWINSZ, &w) < 0 || w.ws_col < 4 || w.ws_row < 4)
		return (0);
	dim[2] = 0;
	dim[3] = len > w.ws_col ? w.ws_col : len;
	while (array[dim[2]])
		dim[2]++;
	dim[1] = w.ws_col / dim[3] ? (dim[2] - 1) / (w.ws_col / dim[3]) + 1
		: dim[2];
	dim[0] = (dim[2] - 1) / dim[1] + 1;
	if (dim[1] > w.ws_row - 1)
		disp_norminette(dim, w.ws_row);
	start = start_display(status, start, dim, tc);
	dim[2] = 0;
	while (array[start + dim[2]] && dim[2] < dim[1] * dim[0])
		dim[2]++;
	dim[4] = ((start ? dim[0] * dim[1] : dim[2]) - 1) / dim[0] + 1;
	dim[5] = start;
	return (display_complex(array + start, dim, status + start, tc));
}
