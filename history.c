#include "parser.h"

void	ft_add_history(char *str)
{
	int		fd;
	char	*list_str;

	fd = open("/tmp/historybash", O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (fd != -1)
	{
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		close(fd);
	}
	errno = 0;
	list_str = ft_strdup(str);
	g_shell.h_list = ft_hlstfirst(g_shell.h_list);
	ft_l_hlstadd_front(&g_shell.h_list, ft_hlstnew(list_str));
	g_shell.list_end = 1;
}

void	ft_read_history(void)
{
	char	*str;

	g_shell.h_list = NULL;
	str = NULL;
	g_shell.fd_history = open ("/tmp/historybash", O_RDONLY, 0644);
	if (g_shell.fd_history != -1)
	{
		while (get_next_line(g_shell.fd_history, &str) == 1)
		{
			ft_l_hlstadd_front(&g_shell.h_list, ft_hlstnew(str));
			str = NULL;
		}
		if (str != NULL)
			free(str);
		close(g_shell.fd_history);
	}
}

char	*ft_history_down(void)
{
	if (!g_shell.h_list)
		return ("");
	if (g_shell.h_list->prev == 0)
	{
		g_shell.list_end = 1;
		return ("");
	}
	g_shell.h_list = g_shell.h_list->prev;
	return (g_shell.h_list->str);
}

char	*ft_history_up(void)
{
	if (g_shell.list_end)
	{
		if (g_shell.h_list)
		{
			g_shell.list_end = 0;
			return (g_shell.h_list->str);
		}
		else
			return ("");
	}
	if (g_shell.h_list->next)
		g_shell.h_list = g_shell.h_list->next;
	return (g_shell.h_list->str);
}
