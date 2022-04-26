/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 08:41:55 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/20 09:01:58 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	skip_spaces(char *line, int *i)
{
	while (line[*i] != 0 && (line[*i] == 32 || line[*i] == 9))
		(*i)++;
}

void	free_all_words(char **words)
{
	int	i;

	i = 0;
	while (words[i] || i == 0)
	{
		free(words[i]);
		i++;
	}
	free(words[i]);
	free(words);
}

void	copy_words(char **words, char **oldwords)
{
	int	i;

	i = 0;
	while (oldwords[i])
	{
		words[i] = oldwords[i];
		i++;
	}
}

char	**copy_env(char **env)
{
	char	**copy;
	int		count;
	int		i;

	count = count_array(env);
	copy = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!copy)
		malloc_error();
	i = 0;
	while (i < count)
	{
		copy[i] = ft_strdup(env[i]);
		if (!copy[i])
			malloc_error();
		i++;
	}
	return (copy);
}

void	malloc_error(void)
{
	ft_putendl_fd("minishell: cannot allocate memory", 2);
	exit(1);
}
