/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:09 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/14 16:31:31 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	is_dir(char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == 0)
		return (S_ISDIR(buf.st_mode));
	return (0);
}

void	print_error(char *name, char *error)
{
	ft_putstr_fd(name, 2);
	ft_putstr_fd(error, 2);
	ft_putchar_fd('\n', 2);
}

void	check_command_type(t_execution *list)
{
	int	size;

	size = ft_lstsize(list);
	ft_execution(list, size);
}

void	no_args(t_execution *list)
{
	int	stdout_copy;
	int	stdin_copy;

	stdout_copy = dup(STDOUT_FILENO);
	stdin_copy = dup(STDIN_FILENO);
	ft_redirection(list->file);
	dup2(stdout_copy, 1);
	dup2(stdin_copy, 0);
}

void	ft_execution(t_execution *list, int size)
{
	t_hr	hr;
	int		pipes[2][2];
	pid_t	*pid;

	hr.i = 0;
	pid = malloc(sizeof(pid_t) * size);
	while (hr.i < size)
	{
		if (list->args[hr.i] == NULL && list->file != NULL)
			no_args(list);
		else if (if_builtin(list->args[0]) != 0 && size == 1)
		{
			check_builtin(list, size);
			break ;
		}
		if (hr.i < size - 1)
			pipe(pipes[hr.i % 2]);
		pid[hr.i] = fork();
		if (pid[hr.i] == 0)
			execute_commands(list, hr, pipes, size);
		close_previous(pipes, hr.i);
		hr.i++;
		list = list->next;
	}
	cleanup(pid, hr);
}
/*
yaaitmou@e1r7p2:~/Desktop/MINI$ echo 'touch "
"' | ./minishell 
minishell: syntax error: unclosed quotes
minishell: syntax error: unclosed quotes
*/