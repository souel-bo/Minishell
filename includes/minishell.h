/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:59:00 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/19 14:49:02 by souel-bo         ###   ########.fr       */
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
	struct s_execution *next;
} t_execution;

# include "libft.h"
# include "tokenizer.h"

const char *type_to_string(t_type type);
t_execution *pre_execution(t_token *tokens);
void	ft_lstdelone_v2(t_execution *lst, void (*del)(void*));
#endif
