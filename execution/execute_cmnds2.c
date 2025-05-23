/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmnds2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:56 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/23 23:54:01 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	permission_notfound(t_execution *list)
{
	perror(list->args[0]);
	if (errno == EACCES)
		g_status()->status = 126;
	else
		g_status()->status = 127;
}

void	scan_cmd(t_execution *list, int size)
{
	if (if_builtin(list->args[0]) != 0)
	{
		is_builtin(list->args[0], list, size);
		free(g_status()->pid);
		ft_freenvp();
		ft_lstclear_v2(&list);
		exit(g_status()->status);
	}
	if (is_dir(list->args[0]))
	{
		g_status()->status = 126;
		print_error(list->args[0], ": Is a directory");
		ft_freenvp();
		ft_lstclear_v2(&list);;
		free(g_status()->pid);
		exit(g_status()->status);
	}
	else if (access(list->args[0], X_OK | F_OK) == 0)
		execute_cmd(list, list->args[0]);
	else
		permission_notfound(list);
	ft_freenvp();
	ft_lstclear_v2(&list);
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
	ft_freenvp();
	free(g_status()->pid);
	ft_lstclear_v2(&list);
	exit(127);
}

void	free_and_exit(void)
{
	free(g_status()->pid);
	exit(g_status()->status);
}
