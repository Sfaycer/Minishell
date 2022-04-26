/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 22:16:46 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 12:01:43 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_front(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if ((ft_strchr(set, s1[i++])) == 0)
			break ;
	}
	return (i - 1);
}

static size_t	ft_back(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1) - 1;
	while (s1[i])
	{
		if ((ft_strchr(set, s1[i])) == 0)
			break ;
		if (i == 0)
			break ;
		else
			i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	k;
	char	*trim;

	if (!s1 || !set)
		return (0);
	i = ft_front(s1, set);
	k = ft_back(s1, set);
	if (i > k)
		k = 0;
	else
		k = k - i + 1;
	trim = ft_substr(s1, i, k);
	return (trim);
}
