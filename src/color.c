#include "ft_select.h"

static void	disp_col(struct stat s)
{
	if ((S_ISVTX & s.st_mode) && (S_IWOTH & s.st_mode)
			&& (S_IXOTH & s.st_mode))
		write(1, "\e[42;30m", 8);
	else if (S_ISDIR(s.st_mode) && S_IRUSR & s.st_mode && S_IWUSR & s.st_mode
			&& S_IXUSR & s.st_mode && S_IRGRP & s.st_mode && S_IWGRP & s.st_mode
			&& S_IXGRP & s.st_mode && S_IROTH & s.st_mode && S_IWOTH & s.st_mode
			&& S_IXOTH & s.st_mode)
		write(1, "\e[43;30m", 8);
	else if (S_ISDIR(s.st_mode))
		write(1, "\e[36;01m", 8);
	else if (S_ISBLK(s.st_mode))
		write(1, "\e[46;34m", 8);
	else if (S_ISCHR(s.st_mode))
		write(1, "\e[43;34m", 8);
	else if (S_ISLNK(s.st_mode))
		write(1, "\e[35m", 5);
	else if (S_ISFIFO(s.st_mode))
		write(1, "\e[33m", 5);
	else if (S_ISSOCK(s.st_mode))
		write(1, "\e[36m", 5);
	else if (S_IXUSR & s.st_mode || S_IXGRP & s.st_mode
			|| S_IXOTH & s.st_mode)
		write(1, "\e[31m", 5);
}

void		color(char *file)
{
	struct stat	buf;

	if (access(file, F_OK) < 0)
		write(0, "\e[2m", 4);
	else if (lstat(file, &buf) == 0)
		disp_col(buf);
}
