#include "parser.h"

char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void	add_symbol(t_term *term)
{
	int	i;

	i = term->iter;
	ft_strcpy(term->tmp, &term->str[term->iter]);
	ft_strcpy(&(term->str[term->iter]), term->buffer);
	term->iter += ft_strlen(term->buffer);
	ft_strcpy(&(term->str[term->iter]), term->tmp);
	write(1, term->buffer, ft_strlen(term->buffer));
	write(1, term->tmp, ft_strlen(term->tmp));
	i = 0;
	while (i++ < (int)ft_strlen(term->tmp))
		write (1, "\e[D", 3);
}

void	pars_esc(t_term *term)
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
		ctrl_d_exit();
	else if (term->buffer[0] > 31)
		add_symbol(term);
}

char	*check_esc(void)
{
	g_shell.term.buffer[0] = '\0';
	g_shell.term.str[0] = '\0';
	g_shell.term.iter = 0;
	while (ft_strncmp(g_shell.term.buffer, "\n", 2))
	{
		g_shell.term.symbol = read(0, g_shell.term.buffer, 999);
		g_shell.term.buffer[g_shell.term.symbol] = '\0';
		pars_esc(&g_shell.term);
	}
	write(1, "\n", 1);
	return (ft_strdup(g_shell.term.str));
}

char	*ft_term(void)
{
	struct termios	term;
	char			*str;

	g_shell.in_term = 1;
	tcgetattr(0, &term);
	tcgetattr(0, &g_shell.term_def);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	tcsetattr(0, TCSANOW, &term);
	tgetent(0, "xterm-256color");
	str = check_esc();
	tcsetattr(0, TCSANOW, &g_shell.term_def);
	g_shell.in_term = 0;
	return (str);
}
