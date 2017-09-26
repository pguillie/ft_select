#ifndef FT_SELECT_H
# define FT_SELECT_H

# include <sys/ioctl.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <termcap.h>
# include <signal.h>
# include <errno.h>

# include <stdio.h>

# define CURSOR 1
# define SELECT 2
# define FIND 4
# define END 8

# define UP 1
# define DOWN 2
# define RIGHT 4
# define LEFT 8

int		g_sig;

typedef struct	s_tc
{
	char	find[128];
	char	data[2048];
	char	buff[2048];
	char	*cd;
	char	*me;
	char	*mr;
	char	*ue;
	char	*up;
	char	*us;
	char	*ve;
	char	*ti;
	char	*te;
	char	*vi;
}				t_tc;

int				sig_action(void);
void			sig_init(void);
int				termcaps(t_tc *tc);
int				raw(struct termios *get);
int				restore(struct termios backup, t_tc tc);
void			init_sig(void);
int				init_status(int status[], int ac);
int				init_len(char *av[]);
int				loop(char *av[], int status[], t_tc tc, int len);
int				term(int n);
void			move(int status[], char move, int line);
int				delete(char *av[], int status[], t_tc tc);
void			selection(int status[]);
int				start_display(int status[], int last, int *dim, t_tc tc);
int				display_string_array(char *av[], int status[], t_tc tc, int l);
void			*ft_memset(void *b, int c, size_t len);
size_t			ft_strlen(char *str);
void			find(char *av[0], int status[], char *find, char byte);
void			tab(int status[]);
void			color(char *str);
void			the_end(char *av[], int status[]);

#endif
