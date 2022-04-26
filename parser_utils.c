/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:23:34 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 12:09:45 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	grammar_message_and_return(char *str)
{
	printf("%s: syntax error near unexpected token `%s'\n",
		g_shell.name, str);
	return (1);
}

void	fully_free_commands(char ***commands)
{
	int	i;
	int	j;

	if (commands)
	{
		i = 0;
		while (commands[i])
		{
			j = 0;
			while (commands[i][j])
				free(commands[i][j++]);
			free(commands[i++]);
		}
		free(commands);
	}
}

static char	***malloc_for_previous_commands(char ***commands)
{
	int		i;
	int		k;
	char	***new;

	i = 0;
	while (commands[i])
		i++;
	new = (char ***)ft_calloc(i + 2, sizeof(char **));
	if (!new)
		malloc_error();
	i = 0;
	while (commands[i])
	{
		k = 0;
		while (commands[i][k])
			k++;
		new[i] = (char **)ft_calloc(k + 1, sizeof(char *));
		if (!new[i])
			malloc_error();
		i++;
	}
	return (new);
}

// frees 3 and 2 level of commands, used in "copy_previous_commands"
static void	free_commands(char ***commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		i++;
	}
	free(commands);
}

char	***copy_previous_commands(char ***commands)
{
	char	***new;
	int		i;
	int		k;

	i = 0;
	while (commands[i])
		i++;
	new = malloc_for_previous_commands(commands);
	if (!new)
		malloc_error();
	i = 0;
	while (commands[i])
	{
		k = 0;
		while (commands[i][k])
		{
			new[i][k] = commands[i][k];
			k++;
		}
		i++;
	}
	free_commands(commands);
	return (new);
}
