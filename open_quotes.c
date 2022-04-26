/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:15:06 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:38:44 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	find_environment_variable(char *arg)
{
	int		i;
	int		j;
	int		arglen;
	char	*temp;

	i = 0;
	arglen = ft_strlen(arg);
	while (g_shell.env[i])
	{
		j = 0;
		while (g_shell.env[i][j] != '=')
			j++;
		temp = ft_substr(g_shell.env[i], 0, j);
		if (!temp)
			malloc_error();
		j = ft_strncmp(arg, temp, arglen);
		if (temp)
			free(temp);
		if (j == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*replace_environment_variable(char *arg)
{
	char	*new;
	int		index;
	int		i;
	int		start;

	index = find_environment_variable(arg);
	if (index == -1)
	{
		return (0);
	}
	i = 0;
	while (g_shell.env[index][i] != '=')
		i++;
	start = ++i;
	i = ft_strlen(g_shell.env[index]);
	new = ft_substr(g_shell.env[index], start, i);
	if (!new)
		malloc_error();
	return (new);
}

char	*open_word_quotes(char *commands)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc_for_open_word_quotes();
	while (commands[j])
	{
		if (commands[j] == '\'')
			new = single_quote_opener(new, commands, &j);
		else if (commands[j] == '\"')
			new = double_quote_opener(new, commands, &j);
		else if (commands[j] == '$')
			new = dollar_sign_opener(new, commands, &j);
		else if (commands[j] == '\\')
			new = backslash_opener(new, commands, &j);
		else
		{
			new = ft_strjoin_free(new, create_str(commands[j]), 3);
			if (!new)
				malloc_error();
			j++;
		}
	}
	return (new);
}

static char	**check_and_trim_array(char **commands, char **old)
{
	char	**new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (commands[i])
		i++;
	while (old[j])
		j++;
	if (i > j)
	{
		new = (char **)ft_calloc(j + 1, sizeof(char *));
		if (!new)
			malloc_error();
		copy_words(new, old);
		free(old);
		return (new);
	}
	return (old);
}

char	**open_quotes(char **commands)
{
	int		i;
	int		j;
	char	**new;

	i = 0;
	while (commands[i])
		i++;
	new = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!new)
		malloc_error();
	i = 0;
	j = 0;
	while (commands[j])
	{
		new[i] = open_word_quotes(commands[j]);
		if (new[i])
			i++;
		j++;
	}
	new = check_and_trim_array(commands, new);
	return (new);
}
