/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:00 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 17:28:16 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	execute_pipeline(int pipes[2][2], t_execution *list,
	t_hr helper, int size)
{
	setup_pipes(pipes, helper.i, size);
	if (list->args[0] == NULL && list->file->file_name != NULL)
	{
		ft_redirection(list->file);
		ft_freenvp();
		ft_lstclear_v2(&g_status()->original_list);
		free_and_exit();
	}
	if (ft_redirection(list->file) == 1)
	{
		ft_freenvp();
		ft_lstclear_v2(&g_status()->original_list);
		free_and_exit();
	}
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
	free(g_status()->pid);
}

void	wait_all(pid_t *pids, t_hr hr)
{
	int	j;
	int	status;

	status = 0;
	j = 0;
	while (j < hr.i)
	{
		g_status()->sig_quit = false;
		g_status()->sig_int_received = false;
		waitpid(pids[j], &status, 0);
		if (WIFSIGNALED(status))
			g_status()->status = WTERMSIG(status) + 128;
		else
			g_status()->status = WEXITSTATUS(status);
		if (WTERMSIG(status) == SIGINT)
			g_status()->sig_int_received = true;
		else if (WTERMSIG(status) == SIGQUIT)
			g_status()->sig_quit = true;
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
