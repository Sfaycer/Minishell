/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 19:08:26 by dkarisa           #+#    #+#             */
/*   Updated: 2020/11/09 13:52:43 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*str;
	size_t	slen;

	slen = ft_strlen(s1);
	str = (char *)malloc((slen + 1) * sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, slen + 1);
	return (str);
}
