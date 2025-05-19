/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:09:14 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/19 12:52:22 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

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
}						t_type;

typedef struct s_token
{
	char				*token;
	t_type				type;
	int					index;
	int heredoc;
	int					expanded;
	struct s_token		*next;
}						t_token;

typedef struct s_list
{
	char				*file_name;
	int					infile;
	int					outfile;
	int					append;
	char				*heredoc;
	struct s_list		*next;
}						t_file;

typedef struct s_execution
{
	char				**args;
	int					infile;
	int					outfile;
	t_file				*file;
	struct s_execution	*next;
}						t_execution;

typedef struct s_status
{
	int					status;
	int                 flag;
	int 				interuppeted;
}						t_status;

typedef struct s_envp
{
	char				*key;
	char				*value;
	int					status;
	int        			flag;
	struct s_envp		*next;
}						t_envp;

typedef struct s_norm
{
	t_token				*token;
	t_execution			*ex;
	t_token				*tokens;
	t_execution			*exec_list;
}						t_norm;

typedef struct s_hr
{
	int i;
	char **path;
} t_hr;

extern t_envp			*g_new_envp;

#endif
