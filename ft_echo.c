/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrady <kbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 05:18:36 by kbrady            #+#    #+#             */
/*   Updated: 2021/07/20 10:52:28 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	ft_echo(char **av, int fd_out)
{
	int	n;
	int	i;
	int	count;

	i = 1;
	n = 0;
	count = count_array(av);
	if (count >= 2)
		if (!ft_strcmp(av[1], "-n"))
			n = 1;
	i = i + n;
	while (av[i])
	{
		ft_putstr_fd(av[i], fd_out);
		if (av[++i])
			ft_putchar_fd(' ', fd_out);
	}
	if (n == 0)
		ft_putchar_fd('\n', fd_out);
	return (1);
}
