/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:02:21 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/20 10:56:34 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	exit_message(int code)
{
	write(2, "exit\n", 5);
	exit(code);
}

void	ft_print_errno(void)
{
	char	*errorbuf;

	errorbuf = strerror(errno);
	ft_putstr_fd(errorbuf, 2);
	write(2, "\n", 1);
}

int	count_array(char **command)
{
	int	i;

	i = 0;
	while (command[i])
		i++;
	return (i);
}

int	buildin_commands(char **command, int fd_out)
{
	int	ret;

	ret = 0;
	errno = 0;
	if (!(ft_strcmp(command[0], "echo")))
		ret = ft_echo(command, fd_out);
	if (!ft_strcmp(command[0], "cd"))
		ret = ft_cd(command);
	if (!ft_strcmp(command[0], "pwd"))
		ret = ft_pwd(fd_out);
	if (!ft_strcmp(command[0], "export"))
		ret = ft_export(command, fd_out);
	if (!ft_strcmp(command[0], "unset"))
		ret = ft_unset(command);
	if (!strcmp(command[0], "env"))
		ret = ft_env(fd_out);
	if (!ft_strcmp(command[0], "exit"))
		ret = ft_exit(command);
	if (ret)
	{
		g_shell.last_pid = 0;
		g_shell.forks++;
		g_shell.status = ret - 1;
	}
	return (ret);
}
