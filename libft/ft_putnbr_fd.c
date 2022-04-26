/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:51:14 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:58:09 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	new_n;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		new_n = n * (-1);
	}
	else
		new_n = n;
	if (new_n >= 10)
		ft_putnbr_fd(new_n / 10, fd);
	ft_putchar_fd(new_n % 10 + 48, fd);
}
