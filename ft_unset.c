/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 02:58:46 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/20 10:51:03 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	not_valid_identifier_message(char *command, int *error)
{
	ft_putstr_fd("minishell: unset: `", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	*error = 2;
}

static void	unset_identifier(char *command)
{
	int	index;
	int	count;

	index = find_environment_variable(command);
	if (index == -1)
		return ;
	count = count_array(g_shell.env);
	free(g_shell.env[index]);
	while (index < count)
	{
		g_shell.env[index] = g_shell.env[index + 1];
		index++;
	}
}

int	ft_unset(char **command)
{
	int	i;
	int	exit_code;

	exit_code = 1;
	i = 1;
	while (command[i])
	{
		if (check_valid_identifier(command[i], 0))
			not_valid_identifier_message(command[i], &exit_code);
		else
			unset_identifier(command[i]);
		i++;
	}
	return (exit_code);
}
