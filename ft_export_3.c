/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 01:31:25 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/21 22:50:02 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*ft_strndup(const char *s1, int count)
{
	char	*str;

	str = (char *)ft_calloc(count + 1, sizeof(char));
	if (!str)
		return (0);
	ft_memcpy(str, s1, count);
	return (str);
}

static void	malloc_env_for_new_variable(char *command, char *name)
{
	char	**new;
	int		count;

	count = count_array(g_shell.env);
	new = (char **)ft_calloc(count + 2, sizeof(char *));
	if (!new)
		malloc_error();
	copy_words(new, g_shell.env);
	if (name)
		new[count] = ft_strjoin_free(name, ft_strchr(command, '='), 1);
	else
		new[count] = ft_strdup(command);
	free(g_shell.env);
	g_shell.env = new;
}

static void	export_set(char *command)
{
	char	*name;
	char	**adress;
	int		index;
	int		count;

	count = ft_strchr(command, '=') - command;
	name = ft_strndup(command, count);
	if (!name)
		malloc_error();
	index = find_environment_variable(name);
	free(name);
	if (index != -1)
	{
		adress = &g_shell.env[index];
		free(g_shell.env[index]);
		*adress = ft_strdup(command);
		if (!*adress)
			malloc_error();
	}
	else
		malloc_env_for_new_variable(command, 0);
}

static void	export_append(char *command)
{
	char	*name;
	char	**adress;
	int		index;
	int		count;

	count = ft_strchr(command, '+') - command;
	name = ft_strndup(command, count);
	if (!name)
		malloc_error();
	index = find_environment_variable(name);
	if (index != -1)
	{
		adress = &g_shell.env[index];
		*adress = ft_strjoin_free(g_shell.env[index], command + count + 2, 1);
		free(name);
		if (!*adress)
			malloc_error();
	}
	else
		malloc_env_for_new_variable(command, name);
}

void	export_set_identifier(char *command)
{
	char	*plus;
	char	*equal;

	equal = ft_strchr(command, '=');
	plus = ft_strchr(command, '+');
	if (equal)
	{
		if (plus && equal == plus + 1)
			export_append(command);
		else
			export_set(command);
	}
}
