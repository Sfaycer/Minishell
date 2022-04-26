/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 22:53:19 by dkarisa           #+#    #+#             */
/*   Updated: 2020/11/11 23:03:17 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*news;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	news = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!news)
		return (0);
	while (s[i])
	{
		news[i] = f(i, s[i]);
		i++;
	}
	news[i] = 0;
	return (news);
}
