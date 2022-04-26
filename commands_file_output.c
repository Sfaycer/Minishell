/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_file_output.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:24:37 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 10:54:53 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	file_desc_output_append(char **commands, int i, int *fd, int fd_out)
{
	char	*tmp;

	if (ft_strncmp(commands[i], ">>", 3) == 0)
	{
		if (*fd && *fd != fd_out)
			close(*fd);
		tmp = open_word_quotes(commands[i + 1]);
		if (!tmp)
			return (1);
		*fd = open(tmp, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

static int	file_desc_output_trunc(char **commands, int i, int *fd, int fd_out)
{
	char	*tmp;

	if (ft_strncmp(commands[i], ">", 2) == 0)
	{
		if (*fd && *fd != fd_out)
			close(*fd);
		tmp = open_word_quotes(commands[i + 1]);
		if (!tmp)
			malloc_error();
		*fd = open(tmp, O_WRONLY | O_CREAT | O_TRUNC, 0644);
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

int	file_desc_output(char **commands, int fd_out)
{
	int	fd;
	int	i;

	if (g_shell.fd_status)
		return (-1);
	fd = fd_out;
	i = 0;
	while (commands[i])
	{
		if (file_desc_output_append(commands, i, &fd, fd_out))
			return (-1);
		if (file_desc_output_trunc(commands, i, &fd, fd_out))
			return (-1);
		i++;
	}
	return (fd);
}
