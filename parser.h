/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbrady <kbrady@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 10:41:30 by dkarisa           #+#    #+#             */
/*   Updated: 2021/07/22 13:49:33 by dkarisa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <stdio.h>
# include <dirent.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <sys/signal.h>
# include <sys/wait.h>
# include <sys/_types/_pid_t.h>
# include <signal.h>

typedef struct s_history_list
{
	char					*str;
	struct s_history_list	*next;
	struct s_history_list	*prev;

}					t_history_list;

typedef struct s_term
{
	char	str[2000];
	char	save_str[2000];
	char	buffer[1000];
	char	tmp[2000];
	int		iter;
	int		symbol;
}	t_term;

typedef struct s_shell
{
	int				status;
	char			**env;
	char			*name;
	int				forks;
	pid_t			last_pid;
	int				fd_history;
	t_history_list	*h_list;
	int				list_end;
	t_term			term;
	struct termios	term_def;
	int				i;
	int				eof;
	int				in_term;
	int				fd_status;
}	t_shell;

t_shell	g_shell;

void			parser_words_handler(char **words);
void			copy_words(char **words, char **oldwords);
void			commands_pipe_or_not(char ***commands);
void			free_commands_in_open_quotes(char **commands);
char			*ft_term(void);
void			parser_init(char *str);
int				file_desc_here_document(char **commands, int i, int *fd,
					int fd_in);

//utils.c
void			skip_spaces(char *line, int *i);
void			free_all_words(char **words);
void			copy_words(char **words, char **oldwords);
char			**copy_env(char **env);
void			malloc_error(void);

//parser_utils.c
char			***copy_previous_commands(char ***commands);
void			fully_free_commands(char ***commands);
int				grammar_message_and_return(char *str);

//commands.c just pipes and command handler
void			commands_pipe_or_not(char ***commands);

//commands_find_path.c everything to find path
char			*find_path_to_command(char *program, int *is_dir);

//commands_execute.c
void			execute_command(char **command, int fd_in, int fd_out);

//commands_file_output.c commands_file_input.c
int				file_desc_output(char **commands, int fd_out);
int				file_desc_input(char **commands, int fd_in);
char			*ft_term_here(void);
char			*heredoc_open_string(char *str);

//commands_utils.c
int				pipe_cycle_count(char ***commands);
void			wait_for_processes(void);
void			trim_command_from_descriptors(char **command);

//open_quotes.c
char			*replace_environment_variable(char *arg);
int				find_environment_variable(char *arg);
char			**open_quotes(char **commands);
char			*open_word_quotes(char *commands);

//open_quotes_utils.c
void			free_commands_in_open_quotes(char **commands);
int				check_for_unclosed_quotes(char *commands, int *j,
					char quote_type);
char			*create_str(char c);
char			*malloc_for_open_word_quotes(void);
char			*backslash_opener(char *old, char *commands, int *j);

//open_quotes_utils_2.c
char			*dollar_sign_opener(char *old, char *commands, int *j);
char			*double_quote_opener(char *old, char *commands, int *j);
char			*single_quote_opener(char *old, char *commands, int *j);

//buildins.c
int				buildin_commands(char **command, int fd_out);
int				ft_free(char **str);
int				ft_strcmp(char *s1, char *s2);
void			ft_print_errno(void);
int				count_array(char **command);
int				ft_pwd(int fd_out);
int				ft_echo(char **av, int fd_out);
int				ft_exit(char **command);
void			exit_message(int code);
int				ft_cd(char **command);
int				ft_env(int fd_out);
int				ft_export(char **command, int fd_out);
void			print_env(int fd_out);
void			export_set_identifier(char *command);
int				check_valid_identifier(char *command, int equal);
int				ft_unset(char **command);

// esc
void			move_left(t_term *tc);
void			move_right(t_term *tc);
void			move_home(t_term *tc);
void			move_end(t_term *tc);
void			ctrl_d_exit(void);
void			back_space(t_term *tc);
void			flush_input(void);
void			history_down(t_term *tc);
void			history_up(t_term *tc);
void			add_symbol(t_term *term);

char			*ft_strcpy(char *dest, const char *src);

// history
t_history_list	*ft_hlstnew(char *str);
t_history_list	*ft_hlstlast(t_history_list *lst);
t_history_list	*ft_hlstfirst(t_history_list *lst);
void			ft_l_hlstadd_front(t_history_list **lst, t_history_list *new);
void			ft_hlstadd_back(t_history_list **lst, t_history_list *new);
void			ft_add_history(char *str);
void			ft_read_history(void);
char			*ft_history_up(void);
char			*ft_history_down(void);

// sig
void			ft_signal_child_process(void);
void			ft_signal(void);
void			ft_signal_here_doc(int sig);
void			ft_signal_child_quit(int sig);

#endif
