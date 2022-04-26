/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_file_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:25:45 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 13:49:04 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/_types/_pid_t.h>

char	*heredoc_open_string(char *str)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc_for_open_word_quotes();
	while (str[j])
	{
		if (str[j] == '$')
			new = dollar_sign_opener(new, str, &j);
		else
		{
			new = ft_strjoin_free(new, create_str(str[j]), 3);
			if (!new)
				malloc_error();
			j++;
		}
	}
	free(str);
	return (new);
}

static int	file_desc_input_file(char **commands, int i, int *fd, int fd_in)
{
	char	*tmp;

	if (ft_strncmp(commands[i], "<", 2) == 0)
	{
		if (*fd && *fd != fd_in)
			close(*fd);
		tmp = open_word_quotes(commands[i + 1]);
		if (!tmp)
			return (1);
		*fd = open(tmp, O_RDONLY);
		if (*fd == -1)
		{
			printf("%s: %s: %s\n", g_shell.name, tmp, strerror(errno));
			free(tmp);
			return (1);
		}
		free(tmp);
	}
	return (0);
}

int	file_desc_input(char **commands, int fd_in)
{
	int	fd;
	int	i;

	if (g_shell.fd_status)
		return (-1);
	fd = fd_in;
	i = 0;
	while (commands[i])
	{
		if (file_desc_input_file(commands, i, &fd, fd_in))
			return (-1);
		if (file_desc_here_document(commands, i, &fd, fd_in))
			return (-1);
		i++;
	}
	return (fd);
}
