/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:00 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/23 14:23:48 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	execute_pipeline(int pipes[2][2], t_execution *list,
	t_hr helper, int size)
{
	setup_pipes(pipes, helper.i, size);
	int (check) = 1;
	if (list->args[0] == NULL && list->file->file_name != NULL)
	{
		check = ft_redirection(list->file);
		exit(check);
	}
	if (ft_redirection(list->file) == 1)
		exit(1);
	execute_cmds(list, helper, size);
	exit(1);
}

void	setup_pipes(int pipes[2][2], int i, int size)
{
	if (i > 0)
		dup2(pipes[(i + 1) % 2][0], STDIN_FILENO);
	close_previous(pipes, i);
	if (i < size - 1)
		dup2(pipes[i % 2][1], STDOUT_FILENO);
	if (i < size - 1)
	{
		close(pipes[i % 2][0]);
		close(pipes[i % 2][1]);
	}
}

void	cleanup(pid_t *pid, t_hr hr)
{
	wait_all(pid, hr);
}

void	wait_all(pid_t *pids, t_hr hr)
{
	int	j;
	int	status;

	j = 0;
	while (j < hr.i)
	{
		waitpid(pids[j], &status, 0);
		g_status()->status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			g_status()->status = WTERMSIG(status) + 128;
		j++;
	}
}

void	close_previous(int pipes[2][2], int i)
{
	if (i > 0)
	{
		close(pipes[(i + 1) % 2][1]);
		close(pipes[(i + 1) % 2][0]);
	}
}
