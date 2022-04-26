#include "parser.h"

void	back_space(t_term *tc)
{
	if (tc->iter > 0)
	{
		tc->iter--;
		write (1, "\e[D", 3);
		write (1, "\e[P", 3);
		ft_memmove(&(tc->str[tc->iter]), &(tc->str[tc->iter + 1]),
			ft_strlen(tc->str + tc->iter));
		if (tc->iter && tc->str[tc->iter - 1] < 0)
		{
			tc->iter--;
			ft_memmove(&(tc->str[tc->iter]), &(tc->str[tc->iter + 1]),
				ft_strlen(tc->str + tc->iter));
			if (tc->str[tc->iter - 1] == -30)
			{
				tc->iter--;
				ft_memmove(&(tc->str[tc->iter]), &(tc->str[tc->iter + 1]),
					ft_strlen(tc->str + tc->iter));
			}
		}
	}
}

void	flush_input(void)
{
	move_end(&g_shell.term);
	while (g_shell.term.iter)
		back_space(&g_shell.term);
}

void	history_up(t_term *tc)
{
	char	*str;

	if (g_shell.list_end == 1)
		ft_strcpy(&(g_shell.term.save_str[0]), g_shell.term.str);
	str = ft_history_up();
	if (str && ft_strlen(str) != 0)
	{
		while (tc->iter-- >= 0)
			write (1, "\e[D", 3);
		write (1, "\e[C", 3);
		tc->iter++;
		write (1, "\e[K", 3);
		ft_strcpy(&(tc->str[0]), str);
		write(1, tc->str, ft_strlen(tc->str));
		tc->iter = ft_strlen(tc->str);
	}
}

void	history_down(t_term *tc)
{
	char	*str;

	if (g_shell.list_end == 1)
		ft_strcpy(&(g_shell.term.save_str[0]), g_shell.term.str);
	str = ft_history_down();
	if (str)
	{
		while (tc->iter-- >= 0)
			write (1, "\e[D", 3);
		write (1, "\e[C", 3);
		tc->iter++;
		write (1, "\e[K", 3);
		if (g_shell.list_end)
			ft_strcpy(&(tc->str[0]), tc->save_str);
		else
			ft_strcpy(&(tc->str[0]), str);
		write(1, tc->str, ft_strlen(tc->str));
		tc->iter = ft_strlen(tc->str);
	}
}
