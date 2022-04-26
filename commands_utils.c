/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:14:11 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/20 10:37:53 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	pipe_cycle_count(char ***commands)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (commands[i])
	{
		if (i >= 3 && i % 2 == 1)
			j++;
		i++;
	}
	return (j);
}

void	wait_for_processes(void)
{
	int		status;
	pid_t	pid;

	while (g_shell.forks)
	{
		pid = wait(&status);
		if (pid == g_shell.last_pid)
		{
			if (WIFEXITED(status))
				g_shell.status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				g_shell.status = 128 + WTERMSIG(status);
		}
		g_shell.forks--;
	}
}

static void	trim_assist_free(char **command, int i)
{
	free(command[i]);
	free(command[i + 1]);
}

static void	trim_assist_annul(char **command, int *count)
{
	command[*count - 2] = 0;
	command[*count - 1] = 0;
	(*count)--;
}

void	trim_command_from_descriptors(char **command)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (command[count])
		count++;
	while (command[i])
	{
		if (ft_strchr("<>", command[i][0]))
		{
			trim_assist_free(command, i);
			j = i;
			while (j < count - 2)
			{
				command[j] = command[j + 2];
				command[j + 1] = command[j + 3];
				j = j + 2;
			}
			trim_assist_annul(command, &count);
		}
		else
			i++;
	}
}
