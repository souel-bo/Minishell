/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/13 17:16:06 by yaaitmou         ###   ########.fr       */
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
	// OR_OPERATOR,
	// AND_OPERATOR
}					t_type;

typedef enum s_flag
{
	ITS_PIPE,
	ITS_BUILTIN,
	ITS_RED_IN,
	ITS_APPEND,
	ITS_RED_OUT,
	ITS_HERE_DOC,
	ITS_CMD
}					t_flag;
typedef struct s_token
{
	char			*token;
	t_type			type;
	struct s_token	*next;
}					t_token;

typedef struct s_operators
{
	char *element;
	t_type type;
}					t_operators;

typedef struct s_new_list
{
	char **args;
	t_flag type;
	int outfd;
	int infd;
	struct s_new_list	*next;
}					t_new_list;


# include "libft.h"
# include "tokenizer.h"
void ft_execution(t_new_list *list);
const char *type_to_string2(t_flag type);
void flag_nodes(t_new_list **node, t_type type);
t_new_list  *ft_create_list(t_token *tokens);
const char *type_to_string(t_type type);
int count_words(t_token *tokens);

#endif
