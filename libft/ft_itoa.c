/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 03:28:49 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:51:58 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static void	fill_number(int n, char *strnum, int i)
{
	unsigned int	new_n;

	if (n < 0)
	{
		strnum[0] = '-';
		strnum++;
		new_n = n * (-1);
		i--;
	}
	else
		new_n = n;
	if (new_n >= 10)
		fill_number(new_n / 10, strnum, i - 1);
	strnum[i - 1] = new_n % 10 + 48;
}

char	*ft_itoa(int n)
{
	int				i;
	int				nb;
	char			*strnum;

	i = 0;
	nb = n;
	if (nb == 0)
		i++;
	while (nb)
	{
		nb = nb / 10;
		i++;
	}
	if (n < 0)
		i++;
	strnum = (char *)malloc((i + 1) * sizeof(char));
	if (!strnum)
		return (0);
	fill_number(n, strnum, i);
	strnum[i] = 0;
	return (strnum);
}
