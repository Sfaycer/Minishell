/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:24:21 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:28:31 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	***handle_pipe_or_semicolon(char ***commands, char c)
{
	int	i;

	i = 0;
	if (commands[0])
		commands = copy_previous_commands(commands);
	if (!commands)
		return (0);
	while (commands[i])
		i++;
	commands[i] = (char **)ft_calloc(2, sizeof(char *));
	if (!commands[i])
		malloc_error();
	commands[i][0] = (char *)ft_calloc(2, sizeof(char));
	if (!commands[i][0])
		malloc_error();
	commands[i][0][0] = c;
	return (commands);
}

char	***handle_words(char ***commands, char **words, int *i)
{
	int	j;
	int	k;

	j = 0;
	if (commands[0])
		commands = copy_previous_commands(commands);
	if (!commands)
		return (0);
	while (commands[j])
		j++;
	k = *i;
	while (words[k] && !ft_strchr("|", words[k][0]))
		k++;
	commands[j] = (char **)ft_calloc(k - *i + 1, sizeof(char *));
	if (!commands[j])
		malloc_error();
	k = 0;
	while (words[*i] && !ft_strchr("|", words[*i][0]))
	{
		commands[j][k++] = ft_strdup(words[(*i)++]);
		if (!commands[j][k - 1])
			malloc_error();
	}
	return (commands);
}

static int	check_grammar(char **words)
{
	int	i;

	i = 0;
	if (ft_strchr("|", words[0][0]))
		return (grammar_message_and_return(words[0]));
	while (words[i])
	{
		if (ft_strchr("<>", words[i][0]))
		{
			if (words[i + 1])
			{
				if (ft_strchr("<>|", words[i + 1][0]))
					return (grammar_message_and_return(words[i + 1]));
			}
			else
				return (grammar_message_and_return("newline"));
		}
		if (ft_strchr("|", words[i][0]))
			if (words[i + 1])
				if (ft_strchr("|", words[i + 1][0]))
					return (grammar_message_and_return(words[i + 1]));
		i++;
	}
	return (0);
}

void	parser_words_handler(char **words)
{
	int		i;
	char	***commands;

	if (check_grammar(words))
		return ;
	commands = (char ***)ft_calloc(2, sizeof(char **));
	if (!commands)
		malloc_error();
	i = 0;
	while (words[i])
	{
		if (ft_strchr("|", words[i][0]))
			commands = handle_pipe_or_semicolon(commands, words[i++][0]);
		else
			commands = handle_words(commands, words, &i);
		if (!commands)
			break ;
	}
	commands_pipe_or_not(commands);
	fully_free_commands(commands);
}
