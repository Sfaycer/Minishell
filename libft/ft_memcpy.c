/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 21:02:27 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:57:28 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*pdst;
	unsigned char	*psrc;

	if (dst == src || n == 0)
		return (dst);
	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	while (n--)
		*pdst++ = *psrc++;
	return (dst);
}
