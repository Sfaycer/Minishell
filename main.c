/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrady <kbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 12:10:53 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 11:36:24 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "parser.h"
#include <sys/termios.h>

static void	set_shlvl(void)
{
	char	*shlvl;
	int		number;
	char	**export;

	shlvl = replace_environment_variable("SHLVL");
	export = (char **)ft_calloc(3, sizeof(char *));
	if (!export)
		malloc_error();
	export[0] = (char *)ft_calloc(1, sizeof(char));
	if (!shlvl)
		export[1] = ft_strdup("SHLVL=1");
	else
	{
		number = ft_atoi(shlvl);
		number++;
		free(shlvl);
		shlvl = ft_itoa(number);
		export[1] = ft_strjoin_free("SHLVL=", shlvl, 2);
	}
	ft_export(export, 0);
	free_commands_in_open_quotes(export);
}

static void	minishell_startup(char *name, char **env)
{
	char	*only_name;

	only_name = ft_strrchr(name, '/');
	if (only_name)
		g_shell.name = only_name + 1;
	else
		g_shell.name = name;
	g_shell.env = copy_env(env);
	g_shell.status = 0;
	g_shell.forks = 0;
	g_shell.h_list = NULL;
	g_shell.list_end = 1;
	g_shell.term.iter = 0;
	g_shell.eof = 0;
	set_shlvl();
	ft_read_history();
}

int	main(int argc, char **argv, char **env)
{
	char	*str;

	(void)argc;
	minishell_startup(argv[0], env);
	while (1)
	{
		ft_signal();
		g_shell.fd_status = 0;
		errno = 0;
		write(1, "minishell$ ", 11);
		str = ft_term();
		if (str[0] != '\0')
			ft_add_history(str);
		if (ft_strlen(str) != 0)
			parser_init(str);
	}
	return (0);
}
