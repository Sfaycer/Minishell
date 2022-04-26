/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_find_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dkarisa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:20:36 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:29:35 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	free_paths(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (paths[i])
			free(paths[i++]);
		free(paths);
	}
}

static char	**paths_split(char *program)
{
	char	*path;
	char	**paths;
	int		i;

	path = replace_environment_variable("PATH");
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		malloc_error();
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin_free(paths[i], "/", 1);
		paths[i] = ft_strjoin_free(paths[i], program, 1);
		if (!paths[i])
			malloc_error();
		i++;
	}
	return (paths);
}

static char	*find_path_to_command_2(char *path, int *is_dir, int is_slash)
{
	struct stat	buf;
	DIR			*dir;
	char		*cmd_path;

	cmd_path = ft_strdup(path);
	if (!cmd_path)
		malloc_error();
	if (stat(cmd_path, &buf) == 0)
	{
		dir = opendir(cmd_path);
		if (dir == 0)
			return (cmd_path);
		*is_dir = 1;
		closedir(dir);
		return (cmd_path);
	}
	errno = 0;
	if (is_slash)
		return (cmd_path);
	free(cmd_path);
	cmd_path = 0;
	return (0);
}

char	*find_path_to_command(char *program, int *is_dir)
{
	char	*path;
	char	**paths;
	int		i;

	if (!program)
		return (0);
	path = 0;
	paths = 0;
	if (ft_strchr(program, '/'))
		path = find_path_to_command_2(program, is_dir, 1);
	else
	{
		paths = paths_split(program);
		if (!paths)
			malloc_error();
		i = 0;
		while (paths[i])
		{
			path = find_path_to_command_2(paths[i++], is_dir, 0);
			if (path)
				break ;
		}
	}
	free_paths(paths);
	return (path);
}
