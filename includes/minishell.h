/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/24 17:47:45 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef enum s_type
{
	TEST,
	WORD,
	BUILTIN,
	ARGUMENT,
	PIPE,
	HERE_DOC,
	DELIMITER,
	APPEND,
	RED_IN,
	RED_OUT,
	FILE_NAME
}					t_type;

typedef struct s_token
{
	char			*token;
	t_type			type;
	struct s_token	*next;
}					t_token;

typedef struct s_execution
{
	char **args;
	int infile;
	int outfile;
	struct s_execution *next;
} t_execution;

# include "libft.h"
# include "tokenizer.h"
# include "expantion.h"
void ifReda(t_execution *list);
int count_pipe_line(t_execution *list);
int	ft_lstsize(t_execution *lst);
void	helper_pipeline(char **path, char **cmd, char **envp);
void execute_pipes(char **path,t_execution *list,char **envp,int size);
char	**get_path();
char	**ft_split(char const *s, char c);
void	execute_simple_cmnd(char **path, t_execution *list, char **envp);
void ft_free(char **ptr);
int ft_isprint(int c);
char	**get_path();
void ft_execution(t_execution *list,char **envp);
const char *type_to_string(t_type type);
t_execution *pre_execution(t_token *tokens);
#endif
