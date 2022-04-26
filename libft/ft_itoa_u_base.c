/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_u_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 15:59:41 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:52:56 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	fill_number(unsigned long n, char *strnum, int i, char *base)
{
	unsigned long	new_n;
	int				baselen;

	baselen = ft_strlen(base);
	new_n = n;
	if (new_n >= (unsigned long)baselen)
		fill_number(new_n / baselen, strnum, i - 1, base);
	strnum[i - 1] = base[new_n % baselen];
}

char	*ft_itoa_u_base(unsigned long n, char *base)
{
	int				i;
	unsigned long	nb;
	char			*strnum;
	int				baselen;

	i = 0;
	nb = n;
	baselen = ft_strlen(base);
	if (nb == 0)
		i++;
	while (nb)
	{
		nb = nb / baselen;
		i++;
	}
	strnum = (char *)malloc((i + 1) * sizeof(char));
	if (!strnum)
		return (0);
	fill_number(n, strnum, i, base);
	strnum[i] = 0;
	return (strnum);
}
