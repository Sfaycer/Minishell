/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 00:09:47 by dkarisa           #+#    #+#             */
/*   Updated: 2020/11/09 14:18:40 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen1;
	size_t	slen2;
	char	*join;

	if (!s1 || !s2)
		return (0);
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	join = (char *)malloc((slen1 + slen2 + 1) * sizeof(char));
	if (!join)
		return (0);
	ft_memcpy(join, s1, slen1);
	ft_memcpy(join + slen1, s2, slen2);
	join[slen1 + slen2] = 0;
	return (join);
}
