/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/19 23:32:58 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:31:50 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	ft_swap(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

static char	**take_names_from_env(int count, char **env)
{
	char	**names;
	int		name_len;
	int		i;

	names = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!names)
		malloc_error();
	i = 0;
	while (env[i])
	{
		name_len = ft_strchr(env[i], '=') - env[i];
		names[i] = (char *)ft_calloc(name_len + 1, sizeof(char));
		if (!names[i])
			malloc_error();
		strlcpy(names[i], env[i], name_len + 1);
		i++;
	}
	return (names);
}

static void	sort_array(int count, char **env)
{
	char	**names;
	int		i;
	int		j;

	names = take_names_from_env(count, env);
	i = 0;
	while (i < count)
	{
		j = count - 1;
		while (j > i)
		{
			if (ft_strcmp(names[j - 1], names[j]) > 0)
			{
				ft_swap(&names[j - 1], &names[j]);
				ft_swap(&env[j - 1], &env[j]);
			}
			j--;
		}
		i++;
	}
	free_commands_in_open_quotes(names);
}

void	print_env(int fd_out)
{
	char	**exp;
	int		i;
	int		name_len;
	int		count;

	exp = copy_env(g_shell.env);
	if (!exp)
		malloc_error();
	count = count_array(exp);
	sort_array(count, exp);
	i = 0;
	while (exp[i])
	{
		ft_putstr_fd("declare -x ", fd_out);
		name_len = ft_strchr(exp[i], '=') - exp[i];
		write(fd_out, exp[i], name_len + 1);
		ft_putstr_fd("\"", fd_out);
		ft_putstr_fd((exp[i] + name_len + 1), fd_out);
		ft_putendl_fd("\"", fd_out);
		i++;
	}
	free_commands_in_open_quotes(exp);
}
