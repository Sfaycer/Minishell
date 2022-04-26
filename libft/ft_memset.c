/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 04:26:40 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:57:42 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*dst;
	unsigned char	symbol;

	dst = (unsigned char *)b;
	symbol = (unsigned char)c;
	while (len--)
		*dst++ = symbol;
	return (b);
}
