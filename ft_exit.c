/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrady <kbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 22:16:29 by kbrady            #+#    #+#             */
/*   Updated: 2021/07/20 10:56:55 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	set_error(int *error)
{
	*error = 1;
	return (0);
}

static int	ft_atoi_and_error(const char *str, int *error)
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
			return (set_error(error));
		if ((final > check || (final == check && (*str - 48) > 8)) && i == -1)
			return (set_error(error));
		final = (final * 10) + (*str - 48);
		str++;
	}
	return ((int)(final * i));
}

static int	is_num(char *ac)
{
	int	i;

	i = 0;
	if (ac[0] == '-' || ac[0] == '+')
		i++;
	while (ac[i])
		if (!ft_isdigit(ac[i++]))
			return (0);
	return (1);
}

static void	wrong_numeric(void)
{
	write(2, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	ft_putendl_fd("numeric argument required", 2);
	exit(255);
}

int	ft_exit(char **command)
{
	int	code;
	int	count;
	int	error;

	count = count_array(command);
	error = 0;
	if (count > 2)
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: ", 17);
		ft_putendl_fd("too many arguments", 2);
		return (2);
	}
	if (count == 1)
		exit_message(0);
	if (is_num(command[1]))
	{
		code = ft_atoi_and_error(command[1], &error);
		if (error)
			wrong_numeric();
		exit_message(code);
	}
	wrong_numeric();
	return (1);
}
