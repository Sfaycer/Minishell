/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes_utils_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrady <kbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:56:27 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:39:36 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*single_quote_opener(char *old, char *commands, int *j)
{
	int		count;
	char	*new;

	count = 0;
	(*j)++;
	if (check_for_unclosed_quotes(commands, j, '\''))
	{
		new = ft_strjoin_free(old, "\'", 1);
		if (!new)
			malloc_error();
		return (new);
	}
	while (commands[*j] && commands[*j] != '\'')
	{
		count++;
		(*j)++;
	}
	new = ft_substr(commands, *j - count, count);
	new = ft_strjoin_free(old, new, 3);
	if (!new)
		malloc_error();
	(*j)++;
	return (new);
}

static void	double_quote_opener_ext(char **new, char *commands, int *j)
{
	if (commands[*j] == '$')
		*new = dollar_sign_opener(*new, commands, j);
	else
	{
		*new = ft_strjoin_free(*new, create_str(commands[*j]), 3);
		(*j)++;
	}
}

char	*double_quote_opener(char *old, char *commands, int *j)
{
	int		count;
	char	*new;

	count = 0;
	(*j)++;
	new = (char *)ft_calloc(1, sizeof(char));
	if (!new)
		malloc_error();
	if (check_for_unclosed_quotes(commands, j, '\"'))
	{
		free(new);
		new = ft_strjoin_free(old, "\"", 1);
		return (new);
	}
	while (commands[*j] && commands[*j] != '\"')
		double_quote_opener_ext(&new, commands, j);
	new = ft_strjoin_free(old, new, 3);
	(*j)++;
	return (new);
}

static char	*dollar_exit_status(int *j, char *old)
{
	char	*new;

	(*j)++;
	new = ft_itoa(g_shell.status);
	new = ft_strjoin_free(old, new, 3);
	if (!new)
		malloc_error();
	return (new);
}

char	*dollar_sign_opener(char *old, char *commands, int *j)
{
	char	*new;
	char	*temp;
	int		i;

	i = *j;
	(*j)++;
	if (commands[*j] == '?')
		return (dollar_exit_status(j, old));
	while (commands[*j] && !ft_strchr("\\\'\"$ ", commands[*j]))
		(*j)++;
	temp = ft_substr(commands, i + 1, *j - i - 1);
	new = replace_environment_variable(temp);
	if (temp)
		free(temp);
	if (i == 0 && !new && (*j == (int)ft_strlen(commands)))
	{
		if (old)
			free(old);
		return (0);
	}
	if (!new)
		new = (char *)ft_calloc(1, sizeof(char));
	new = ft_strjoin_free(old, new, 3);
	return (new);
}
