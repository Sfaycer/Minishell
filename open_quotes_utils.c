/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 09:39:55 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:06:58 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

//frees 2 and 1 level of commands, used in open_quotes
void	free_commands_in_open_quotes(char **commands)
{
	int	i;

	i = 0;
	while (commands[i])
	{
		free(commands[i]);
		commands[i] = 0;
		i++;
	}
	free(commands);
}

int	check_for_unclosed_quotes(char *commands, int *j, char quote_type)
{
	int	i;

	i = *j;
	while (commands[i])
	{
		if (commands[i] == quote_type)
			break ;
		i++;
	}
	if (commands[i])
		return (0);
	return (1);
}

char	*create_str(char c)
{
	char	*new;

	new = (char *)ft_calloc(2, sizeof(char));
	if (!new)
		malloc_error();
	new[0] = c;
	return (new);
}

char	*malloc_for_open_word_quotes(void)
{
	char	*new;

	new = (char *)ft_calloc(1, sizeof(char));
	if (!new)
		malloc_error();
	return (new);
}

char	*backslash_opener(char *old, char *commands, int *j)
{
	char	*new;

	(*j)++;
	if (commands[*j] == 0)
	{
		new = create_str('\\');
		(*j)--;
	}
	else
		new = create_str(commands[*j]);
	if (!old)
		old = (char *)ft_calloc(1, sizeof(char));
	new = ft_strjoin_free(old, new, 3);
	if (!new)
		malloc_error();
	(*j)++;
	return (new);
}
