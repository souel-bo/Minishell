/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmnds2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:56 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/23 16:20:28 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	scan_cmd(t_execution *list)
{
	if (is_dir(list->args[0]))
	{
		g_status()->status = 126;
		print_error(list->args[0], ": Is a directory");
		ft_freeEnvp();
		free(g_status()->pid);
		exit(g_status()->status);
	}
	else if (access(list->args[0], X_OK | F_OK) == 0)
		execute_cmd(list, list->args[0]);
	else
	{
		perror(list->args[0]);
		if (errno == EACCES)
			g_status()->status = 126;
		else
			g_status()->status = 127;
	}
	ft_freeEnvp();
	free(g_status()->pid);
	exit(g_status()->status);
}

void	child(t_execution *list, t_hr hr, int pipes[2][2], int size)
{
	sig_child();
	execute_commands(list, hr, pipes, size);
}

void	command_not_found(t_execution *list)
{
	g_status()->status = 127;
	print_error(list->args[0], ": command not found");
	ft_freeEnvp();
	free(g_status()->pid);
	exit(127);
}

void	free_and_exit(void)
{
	free(g_status()->pid);
	exit(g_status()->status);
}
