#include "parser.h"

void	ft_signal_cltr_c(int sig)
{
	(void)sig;
	g_shell.status = 1;
	write(1, "\n", 1);
	flush_input();
	if (g_shell.in_term)
		write(1, "minishell$ ", 11);
}

void	ft_signal_here_doc(int sig)
{
	(void)sig;
	tcsetattr(0, TCSANOW, &g_shell.term_def);
	exit(1);
}

void	ft_signal_child_quit(int sig)
{
	write(1, "\b\b  \b\b", 6);
	write(1, "^\\Quit: ", 8);
	ft_putnbr_fd(sig, 1);
	write(1, "\n", 1);
}

void	ft_signal(void)
{
	signal(SIGINT, ft_signal_cltr_c);
	signal(SIGQUIT, SIG_IGN);
}
