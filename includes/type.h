/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 21:09:14 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 19:50:12 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_H
# define TYPE_H

# include <stdbool.h>
# include <sys/types.h>

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
	int					heredoc;
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

typedef struct s_norm_v2
{
	char				*s;
	char				*temp;
	char				*l;
	int					i;
	int					j;
	int					k;
	int					n;
}						t_norm_v2;

typedef struct s_execution
{
	char				**args;
	int					infile;
	int					outfile;
	t_file				*file;
	struct s_execution	*next;
}						t_execution;

typedef struct s_envp
{
	char				*key;
	char				*value;
	int					status;
	struct s_envp		*next;
}						t_envp;
typedef struct s_status
{
	t_execution			*original_list;
	int					stdout_copy;
	int					stdin_copy;
	t_envp				*new_envp;
	int					interuppeted;
	int					status;
	pid_t				*pid;
	int					flag;
	bool				sig_quit;
	bool				sig_int_received;
}						t_status;

typedef struct s_here_doc
{
	int					fd;
	char				*delimiter;
	int					flag;
	t_token				*tokens;
	char				*file_nm;
}						t_here_doc;

typedef struct s_norm
{
	t_token				*token;
	t_execution			*ex;
	t_token				*tokens;
	t_execution			*exec_list;
}						t_norm;

typedef struct s_hr
{
	int					i;
	char				**path;
}						t_hr;

// extern t_envp			*g_new_envp;

#endif
