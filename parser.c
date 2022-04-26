/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 08:40:53 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:37:39 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	parser_found_quotes(char *str, int *i)
{
	char	c;

	c = str[*i];
	(*i)++;
	if (c == '\'')
	{
		while (str[*i] && str[*i] != c)
			(*i)++;
	}
	else
	{
		while (str[*i] && (str[*i] != c))
		{
			if (str[*i] == '\\' && str[*i + 1])
				(*i)++;
			(*i)++;
		}
	}
	if (str[*i] == 0)
		(*i)--;
}

static void	parser_found_special_symbol(char *str, int *i)
{
	static int	indent;

	if (indent)
		*i += indent;
	while (indent == 0 && str[*i] && !ft_isspace(str[*i])
		&& !ft_strchr("|<>", str[*i]))
	{
		if (str[*i] == '\"' || str[*i] == '\'')
			parser_found_quotes(str, i);
		if (str[*i] == '\\')
			(*i)++;
		if (str[*i])
			(*i)++;
	}
	indent = 0;
	if (str[*i] && ft_strchr("|<>", str[*i]))
	{
		indent++;
		if ((str[*i] == '>' && str[*i + 1] == '>')
			|| (str[*i] == '<' && str[*i + 1] == '<'))
			indent++;
	}
}

static char	**parser_found_word(char *str, int *i, char **oldwords)
{
	int			j;
	static int	k;
	char		**words;

	words = (char **)ft_calloc(k + 2, sizeof(char *));
	if (!words)
		malloc_error();
	if (k != 0)
		copy_words(words, oldwords);
	j = *i;
	parser_found_special_symbol(str, i);
	if (j != *i)
		words[k] = ft_substr(str, j, *i - j);
	if (k != 0)
		free(oldwords);
	skip_spaces(str, i);
	if (j != *i)
		k++;
	if (str[*i] == 0)
		k = 0;
	return (words);
}

void	parser_init(char *str)
{
	char	**words;
	int		i;

	i = 0;
	words = 0;
	if (!str)
		return ;
	while (str[i])
	{
		skip_spaces(str, &i);
		words = parser_found_word(str, &i, words);
	}
	if (!words)
	{
		return ;
	}
	if (words[0])
		parser_words_handler(words);
	if (i)
		free_all_words(words);
	free(str);
}
