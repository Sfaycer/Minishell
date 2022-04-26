#include "parser.h"

void	move_left(t_term *tc)
{
	if (tc->iter > 0)
	{
		write (1, "\e[D", 3);
		tc->iter--;
		if (tc->iter && tc->str[tc->iter - 1] < 0)
		{
			tc->iter--;
			if (tc->str[tc->iter - 1] == -30)
				tc->iter--;
		}
	}
}

void	move_right(t_term *tc)
{
	tc->symbol = (int)ft_strlen(tc->str);
	if (tc->iter < tc->symbol)
	{
		write (1, "\e[C", 3);
		tc->iter++;
		if (tc->iter && tc->str[tc->iter - 1] < 0)
		{
			tc->iter++;
			if (tc->str[tc->iter - 1] == -30)
				tc->iter++;
		}
	}
}

void	move_home(t_term *tc)
{
	while (tc->iter-- != 0)
		write (1, "\e[D", 3);
	tc->iter++;
}

void	move_end(t_term *tc)
{
	tc->symbol = ft_strlen(tc->str);
	while (tc->iter++ < tc->symbol)
		write (1, "\e[C", 3);
	tc->iter--;
}

void	ctrl_d_exit(void)
{
	write(1, "exit\n", 5);
	tcsetattr(0, TCSANOW, &g_shell.term_def);
	exit(0);
}
