/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 23:29:58 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:59:51 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			count++;
			while (*s && !(*s == c))
				s++;
		}
	}
	return (count);
}

static char	*get_word(char const *s, char c)
{
	size_t	i;
	char	*word;

	i = 0;
	while (s[i] && !(s[i] == c))
		i++;
	word = (char *)malloc((i + 1) * sizeof(char));
	if (!word)
		return (0);
	i = 0;
	while (s[i] && !(s[i] == c))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

char	**free_all(char **words)
{
	size_t	i;

	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	size_t	words;
	size_t	i;

	if (!s)
		return (0);
	words = word_count(s, c);
	split = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!split)
		return (0);
	i = 0;
	while (*s)
	{
		while (*s && (*s == c))
			s++;
		if (*s)
		{
			split[i] = get_word(s, c);
			if (!split[i++])
				return (free_all(split));
			while (*s && !(*s == c))
				s++;
		}
	}
	return (split);
}
