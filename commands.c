/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:31:01 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:28:50 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	command_handler(char **command, int pipe_in, int pipe_out)
{
	int	fd_in;
	int	fd_out;

	fd_in = file_desc_input(command, pipe_in);
	fd_out = file_desc_output(command, pipe_out);
	if (fd_in == -1 || fd_out == -1)
	{
		g_shell.status = 1;
		g_shell.fd_status = 0;
		return ;
	}
	trim_command_from_descriptors(command);
	if (command[0])
	{
		command = open_quotes(command);
		execute_command(command, fd_in, fd_out);
		free_commands_in_open_quotes(command);
	}
	if (pipe_in != fd_in)
		close(fd_in);
	if (pipe_out != fd_out)
		close(fd_out);
}

static void	pipe_handler_child_ext(char ***commands, int cycles, int pipe_in,
		int pipe_out)
{
	int	pipe_fd[2];
	int	i;

	i = 2;
	while (cycles)
	{
		close(pipe_out);
		pipe(pipe_fd);
		pipe_out = pipe_fd[1];
		command_handler(commands[i], pipe_in, pipe_out);
		i = i + 2;
		close(pipe_in);
		pipe_in = pipe_fd[0];
		cycles--;
	}
	close(pipe_out);
	command_handler(commands[i], pipe_in, 0);
	close(pipe_in);
}

static void	pipe_handler_child(char ***commands)
{
	int	i;
	int	cycles;
	int	pipe_fd[2];
	int	pipe_in;
	int	pipe_out;

	cycles = pipe_cycle_count(commands);
	pipe(pipe_fd);
	pipe_in = pipe_fd[0];
	pipe_out = pipe_fd[1];
	i = 0;
	command_handler(commands[i], 0, pipe_out);
	i = i + 2;
	pipe_handler_child_ext(commands, cycles, pipe_in, pipe_out);
}

static void	pipe_handler(char ***commands)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		errno = 0;
		signal(SIGINT, ft_signal_here_doc);
		pipe_handler_child(commands);
		wait_for_processes();
		exit(g_shell.status);
	}
	else if (pid < 0)
		printf("fork: %s\n", strerror(errno));
	else
	{
		g_shell.last_pid = pid;
		g_shell.forks++;
	}
}

void	commands_pipe_or_not(char ***commands)
{
	if (!commands)
		return ;
	if (commands[1])
		pipe_handler(commands);
	else
		command_handler(commands[0], 0, 0);
	wait_for_processes();
}
