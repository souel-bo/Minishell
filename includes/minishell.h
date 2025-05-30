/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 23:16:18 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "expantion.h"
# include "here_doc.h"
# include "libft.h"
# include "tokenizer.h"
# include "type.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# define ALLOC 409600
# define SINGLE_QUOTE -2
# define DOUBLE_QUOTE -1

void		free_after_exit(void);
void		single_command(t_execution *list, t_hr hr, int size);
void		redir_free(t_execution *list);
int			find_dollar(char *s);
int			is_special(char c);
void		join_value(char *temp, const char *s, int *j);
char		*expand_env(char *key);
void		set_env_var(char *key, char *value);
int			start(char *input);
char		*setup_input(void);
void		check_number(t_execution *input, int size);
void		command_not_found(t_execution *list);
int			array_len(char **args);
void		cmdwithpath(t_execution *list, char **path, int size);
int			checkifnum(char *number);
int			ft_open(char *file_name, int flag, int in_out);
char		*ft_itoa(int n);
t_status	*g_status(void);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
char		*searchandsave(char *var);
int			search_in_env(char *var);
int			change_in_env(char *var, char *buf);
void		ft_exit(t_execution *input, int size);
int			ft_redirection(t_file *file);
int			if_builtin(char *cmd);
void		ft_pwd(void);
void		ft_unset(t_execution *list);
void		ft_export(t_execution *list);
void		is_builtin(char *cmd, t_execution *list, int size);
void		ft_unset(t_execution *list);
char		**listtoarray(void);
void		ft_env(void);
void		ft_unset(t_execution *list);
t_envp		*ft_create_envp(char **envp);
void		ft_lstadd_back2(t_envp **lst, t_envp *new);
t_envp		*new_element2(char *line);
int			countlenkey(char *line);
void		unset_var(t_envp *prev, t_envp *current);
void		export_signle(t_envp *export);
void		child(t_execution *list, t_hr hr, int pipes[2][2], int size);
int			ft_lstsize_envp(t_envp *lst);
int			ft_lstsize(t_execution *lst);
char		**get_path(void);
void		free_and_exit(void);
char		**ft_split(char const *s, char c);
void		ft_free(char **ptr);
int			ft_isprint(int c);
char		**get_path(void);
void		ft_execution(t_execution *list, int size);
const char	*type_to_string(t_type type);
t_execution	*pre_execution(t_token *tokens);
t_token		*handle_heredoc(t_token *tokens);
void		ft_freenvp(void);
void		check_command_type(t_execution *list);
void		check_builtin(t_execution *list, int size);
void		setup_pipes(int pipes[2][2], int i, int size);
void		execute_cmds(t_execution *list, t_hr hr, int size);
void		close_previous(int pipes[2][2], int i);
void		wait_all(pid_t *pids, t_hr hr);
int			check_sen(char *list);
void		print_error(char *name, char *error);
void		print_error2(char *name, char *error, char *message, int status);
void		execute_commands(t_execution *list, t_hr hr, int pipes[2][2],
				int size);
t_envp		*ft_lstlast2(t_envp *lst);
void		scan_cmd(t_execution *list, int size);
void		handler(int sig);
void		sig_child(void);
void		cleanup(pid_t *pid, t_hr hr);
int			already_in(char *arg);
int			checkifnum(char *number);
void		ft_echo(t_execution *input);
void		ft_chdir(t_execution *input);
int			is_dir(char *path);
int			is_valid(t_execution *list);
void		execute_pipeline(int pipes[2][2], t_execution *list, t_hr helper,
				int size);
int			execute_cmd(t_execution *list, char *cmd);
void		num_error(t_execution *input, int size);
#endif
