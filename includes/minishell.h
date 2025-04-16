/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/16 22:17:26 by yaaitmou         ###   ########.fr       */
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
	int append_flag;
	int heredoc;
	struct s_execution *next;
} t_execution;

# include "libft.h"
# include "tokenizer.h"
void ft_free(char **ptr);
int ft_isprint(int c);
char	**get_path();
void ft_execution(t_execution *list,char **envp);
const char *type_to_string(t_type type);
t_execution *pre_execution(t_token *tokens);
#endif
