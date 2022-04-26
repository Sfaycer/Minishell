/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:08:03 by dkarisa           #+#    #+#             */
/*   Updated: 2020/11/21 06:51:35 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*str;
	char		symbol;

	str = &s[ft_strlen(s)];
	symbol = (char)c;
	while (str >= s)
	{
		if (*str == symbol)
			return ((char *)str);
		str--;
	}
	return (0);
}
