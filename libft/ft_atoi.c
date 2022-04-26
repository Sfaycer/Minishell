/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:48:36 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:49:41 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int				i;
	unsigned long	final;
	unsigned long	check;

	i = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	final = 0;
	check = 922337203685477580;
	while (ft_isdigit(*str))
	{
		if ((final > check || (final == check && (*str - 48) > 7)) && i == 1)
			return (-1);
		if ((final > check || (final == check && (*str - 48) > 8)) && i == -1)
			return (0);
		final = (final * 10) + (*str - 48);
		str++;
	}
	return ((int)(final * i));
}
