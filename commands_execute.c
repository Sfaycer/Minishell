/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrady <kbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:28:42 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:29:11 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	execve_execute(char *program, char **command, int fd_in, int fd_out)
{
	int	save_out;

	save_out = dup(1);
	if (fd_in)
		dup2(fd_in, 0);
	if (fd_out)
		dup2(fd_out, 1);
	if (execve(program, command, g_shell.env) == -1)
	{
		dup2(save_out, 1);
		printf("%s: %s: %s\n", g_shell.name, program, strerror(errno));
		free(program);
		if (errno == 13)
			exit (126);
		exit(127);
	}
}

void	child_process(char **command, int fd_in, int fd_out)
{
	char	*program;
	int		is_dir;

	is_dir = 0;
	program = find_path_to_command(command[0], &is_dir);
	if (program && command[0][0] != 0)
	{
		if (is_dir)
		{
			printf("%s: %s: is a directory\n", g_shell.name, program);
			exit(126);
		}
		else
			execve_execute(program, command, fd_in, fd_out);
	}
	else
	{
		printf("%s: %s: command not found\n", g_shell.name, command[0]);
		exit(127);
	}
}

void	execute_command(char **command, int fd_in, int fd_out)
{
	pid_t	pid;

	if (!command[0])
		return ;
	if (buildin_commands(command, fd_out))
		return ;
	pid = fork();
	if (pid == 0)
	{
		errno = 0;
		signal(SIGTERM, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, ft_signal_child_quit);
		child_process(command, fd_in, fd_out);
	}
	else if (pid < 0)
		printf("fork: %s\n", strerror(errno));
	else
	{
		signal(SIGQUIT, ft_signal_child_quit);
		g_shell.forks++;
		g_shell.last_pid = pid;
	}
}
