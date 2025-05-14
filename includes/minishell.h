/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/14 21:13:27 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "type.h"
# include "expantion.h"
# include "tokenizer.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "libft.h"

char		*ft_itoa(int n);
t_status	*g_status(void);
int			ft_isdigit(int c);
int			ft_isalpha(int c);
char		*searchAndsave(char *var);
int			search_in_env(char *var);
int			change_in_env(char *var, char *buf);
void		ft_exit(t_execution *input, int size);
void		ft_redirection(t_file *file);
int			if_builtin(char *cmd);
void		ft_pwd(void);
void		ft_unset(t_execution *list);
void		ft_export(t_execution *list);
void		is_builtin(char *cmd, t_execution *list, int size);
void		ft_unset(t_execution *list);
char		**listToArray(void);
void		ft_env(void);
void		ft_unset(t_execution *list);
t_envp		*ft_create_envp(char **envp);
void		ft_lstadd_back2(t_envp **lst, t_envp *new);
t_envp		*new_element2(char *line);
int			CountLenKey(char *line);
int			count_pipe_line(t_execution *list);
int			ft_lstsize_envp(t_envp *lst);
int			ft_lstsize(t_execution *lst);
void		execute_pipes(char **path, t_execution *list, int size);
char		**get_path(void);
char		**ft_split(char const *s, char c);
void		execute_simple_cmnd(char **path, t_execution *list, int size);
void		ft_free(char **ptr);
int			ft_isprint(int c);
char		**get_path(void);
void		ft_execution(t_execution *list);
const char	*type_to_string(t_type type);
t_execution	*pre_execution(t_token *tokens);
int			handle_heredoc(t_norm *norm, t_file *element);
void		ft_freeEnvp(void);
void		print(t_execution *list, t_token *list2);
#endif
