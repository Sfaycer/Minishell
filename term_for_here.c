#include "parser.h"

void	pars_esc_here(t_term *term)
{
	if (!ft_strncmp(term->buffer, "\e[A", 3))
		history_up(term);
	else if (!ft_strncmp(term->buffer, "\e[B", 3))
		history_down(term);
	else if (!ft_strncmp(term->buffer, "\e[D", 3))
		move_left(term);
	else if (!ft_strncmp(term->buffer, "\e[C", 3))
		move_right(term);
	else if (!ft_strncmp(term->buffer, "\177", 4))
		back_space(term);
	else if (!ft_strncmp(term->buffer, "\e[H", 3))
		move_home(term);
	else if (!ft_strncmp(term->buffer, "\e[F", 3))
		move_end(term);
	else if (!ft_strncmp(term->buffer, "\4", 2) && term->iter == 0)
		g_shell.eof = 1;
	else if (term->buffer[0] > 31)
		add_symbol(term);
}

char	*check_esc_here(void)
{
	g_shell.term.buffer[0] = '\0';
	g_shell.term.str[0] = '\0';
	g_shell.term.iter = 0;
	while (ft_strncmp(g_shell.term.buffer, "\n", 2) && !g_shell.eof)
	{
		g_shell.term.symbol = read(0, g_shell.term.buffer, 999);
		g_shell.term.buffer[g_shell.term.symbol] = '\0';
		pars_esc_here(&g_shell.term);
	}
	if (g_shell.eof == 0)
		write(1, "\n", 1);
	return (ft_strdup(g_shell.term.str));
}

char	*ft_term_here(void)
{
	struct termios	term;
	char			*str;

	tcgetattr(0, &term);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
	str = check_esc_here();
	tcsetattr(0, TCSANOW, &g_shell.term_def);
	return (str);
}
