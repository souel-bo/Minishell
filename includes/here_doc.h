/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:20:48 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 19:56:46 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "minishell.h"
# include "type.h"
# define HERE_DOC_FILE "/tmp/.here_doc"

t_token	*handle_heredoc(t_token *tokens);
int		process_heredoc(t_token *here_token, t_token **tokens);
int		read_here_doc(t_here_doc *here, char *delimiter, int flag,
			t_token *tokens);
void	child_here_doc(char *input, t_token *tokens, t_here_doc *here,
			int flag);
void	exit_normal(t_token *tokens, char *file_nm, int fd, char *input);
void	exit_ctrl_c(t_token *tokens, char *file_nm, int fd);
void	exit_ctrl_d(t_token *tokens, char *file_nm, int fd);
char	*expand_here_doc(char *input);
char	*clean_and_replace(char *input, t_norm_v2 *obj);
void	expand(char *input, t_norm_v2 *obj);
void	initialize_obj(t_norm_v2 *obj);
void	expand_value_here_doc(char *input, t_norm_v2 *obj);
void	copy_variables_here(char *input, t_norm_v2 *obj);
int		copy_character(char *input, t_norm_v2 *obj);
pid_t	fork_here_doc(void);
void	here_doc_handler(int i);
char	*file_name(void);
#endif