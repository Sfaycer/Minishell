#include "parser.h"

static char	*remalloc_word(char *word, char c)
{
	char	*tmp;
	int		i;

	tmp = (char *)ft_calloc(ft_strlen(word) + 2, sizeof(char));
	if (!tmp)
		malloc_error();
	i = 0;
	while (word[i])
	{
		tmp[i] = word[i];
		i++;
	}
	tmp[i] = c;
	free(word);
	return (tmp);
}

static char	*open_quotes_check(char *word, int *expand)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = (char *)ft_calloc(1, sizeof(char));
	if (!tmp)
		malloc_error();
	while (word[i])
	{
		if (ft_strchr("\'\"", word[i]))
			*expand = 0;
		else
			tmp = remalloc_word(tmp, word[i]);
		i++;
	}
	return (tmp);
}

static void	child_heredoc(int *fd, char *tmp, int expand)
{
	char	*str;

	*fd = open("/tmp/heredocbash", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (g_shell.eof == 0)
	{
		write(1, "> ", 2);
		str = ft_term_here();
		if (ft_strcmp(str, tmp) == 0)
			g_shell.eof = 1;
		else
		{
			if (expand)
				str = heredoc_open_string(str);
			write(*fd, str, ft_strlen(str));
			if (g_shell.eof == 0)
				write(*fd, "\n", 1);
		}
		free(str);
	}
	close(*fd);
	exit(0);
}

static void	forked_input(int *fd, char *tmp, int expand)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, ft_signal_here_doc);
		child_heredoc(fd, tmp, expand);
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_shell.fd_status = WEXITSTATUS(status);
	}
}

int	file_desc_here_document(char **commands, int i, int *fd, int fd_in)
{
	char	*tmp;
	int		expand;

	if (ft_strncmp(commands[i], "<<", 3) == 0)
	{
		if (*fd && *fd != fd_in)
			close(*fd);
		expand = 1;
		tmp = open_quotes_check(commands[i + 1], &expand);
		forked_input(fd, tmp, expand);
		free(tmp);
		g_shell.eof = 0;
		if (g_shell.fd_status)
			return (1);
		*fd = open("/tmp/heredocbash", O_RDONLY);
		if (*fd == -1)
		{
			printf("%s: %s: %s\n", g_shell.name, tmp, strerror(errno));
			free(tmp);
			return (1);
		}
	}
	return (0);
}
