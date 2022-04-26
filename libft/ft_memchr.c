/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 22:45:58 by dkarisa           #+#    #+#             */
/*   Updated: 2020/11/21 06:14:31 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	unsigned char		symbol;

	p = (const unsigned char *)s;
	symbol = (unsigned char)c;
	while (n--)
	{
		if (*p == symbol)
			return ((void *)p);
		p++;
	}
	return (0);
}
