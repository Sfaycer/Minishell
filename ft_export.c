/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 20:36:06 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:31:44 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"

int	check_valid_identifier(char *command, int equal)
{
	int	i;

	i = 0;
	if (!ft_isalpha(command[i]) && command[i] != '_')
		return (1);
	i++;
	while (command[i])
	{
		if (equal && (command[i] == '=' || (command[i] == '+'
					&& command[i + 1] == '=')))
			break ;
		if (!ft_isalnum(command[i]) && !ft_isdigit(command[i])
			&& command[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static void	not_valid_identifier_message(char *command, int *error)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(command, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	*error = 2;
}

int	ft_export(char **command, int fd_out)
{
	int		count;
	int		i;
	int		exit_code;

	count = count_array(command);
	exit_code = 1;
	if (count == 1)
		print_env(fd_out);
	else
	{
		i = 1;
		while (command[i])
		{
			if (check_valid_identifier(command[i], 1))
				not_valid_identifier_message(command[i], &exit_code);
			else
				export_set_identifier(command[i]);
			i++;
		}
	}
	return (exit_code);
}
