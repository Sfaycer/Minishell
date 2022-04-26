/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrady <kbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 23:25:13 by kbrady            #+#    #+#             */
/*   Updated: 2021/07/22 12:49:09 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h" 

static char	**create_array_for_export(char *pwd, int oldpwd)
{
	char	**array;

	array = (char **)ft_calloc(3, sizeof(char *));
	if (!array)
		malloc_error();
	array[0] = (char *)ft_calloc(1, sizeof(char));
	if (oldpwd)
		array[1] = ft_strjoin_free("OLDPWD=", pwd, 0);
	else
		array[1] = ft_strjoin_free("PWD=", pwd, 2);
	if (!array[0] || !array[1])
		malloc_error();
	return (array);
}

static void	change_pwds(char *prevpwd)
{
	char	*pwd;
	char	*oldpwd;
	char	*curpwd;
	char	**command;

	oldpwd = replace_environment_variable("OLDPWD");
	pwd = replace_environment_variable("PWD");
	if (oldpwd)
	{
		command = create_array_for_export(prevpwd, 1);
		ft_export(command, 0);
		free(oldpwd);
		free_commands_in_open_quotes(command);
	}
	if (pwd)
	{
		curpwd = getcwd(0, 0);
		if (!curpwd)
			malloc_error();
		command = create_array_for_export(curpwd, 0);
		ft_export(command, 0);
		free(pwd);
		free_commands_in_open_quotes(command);
	}
}

static int	cd_error_message(int home)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (home)
		ft_putendl_fd("HOME not set", 2);
	else
		ft_print_errno();
	return (2);
}

static int	error_return(char *pwd)
{
	free(pwd);
	return (cd_error_message(0));
}

int	ft_cd(char **command)
{
	char	*path;
	char	*pwd;
	int		count;

	count = count_array(command);
	if (count == 1)
	{
		path = replace_environment_variable("HOME");
		if (!path)
			return (cd_error_message(1));
	}
	else
		path = command[1];
	pwd = getcwd(0, 0);
	if (!pwd)
		malloc_error();
	chdir(path);
	if (errno)
		return (error_return(pwd));
	change_pwds(pwd);
	if (count == 1)
		free(path);
	free(pwd);
	return (1);
}
