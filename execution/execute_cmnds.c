/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmnds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:53 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 15:28:20 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	execute_cmd(t_execution *list, char *cmd)
{
	char	**env_char;

	env_char = listtoarray();
	execve(cmd, list->args, env_char);
	free(cmd);
	ft_free(env_char);
	ft_lstclear_v2(&g_status()->original_list);
	exit(127);
}

void	cmdwithpath(t_execution *list, char **path, int size)
{
	(void)path;
	if (if_builtin(list->args[0]) != 0)
	{
		is_builtin(list->args[0], list, size);
		free(g_status()->pid);
		ft_freenvp();
		ft_lstclear_v2(&g_status()->original_list);
		exit(g_status()->status);
	}
	else if (ft_strchr(list->args[0], '/'))
		scan_cmd(list, size);
	else if (is_dir(list->args[0]))
	{
		command_not_found(list);
	}
	else if (is_valid(list) == 1)
		command_not_found(list);
}

void	execute_cmds(t_execution *list, t_hr hr, int size)
{
	if (search_in_env("PATH"))
		cmdwithpath(list, hr.path, size);
	else
		scan_cmd(list, size);
}

void	execute_commands(t_execution *list, t_hr hr, int pipes[2][2], int size)
{
	if (list->args[0] == NULL && list->file->file_name != NULL && size == 1)
	{
		redir_free(list);
		free_and_exit();
	}
	if (size == 1 && list->args[0])
		single_command(list, hr, size);
	else if (size > 1)
		execute_pipeline(pipes, list, hr, size);
}

int	is_valid(t_execution *list)
{
	char	*tmp;
	char	*full_cmd;
	char	**paths;

	int (i) = 0;
	if ((list->args[0] == NULL) || (list->args[0][0] == '\0'))
		return (1);
	paths = get_path();
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_cmd = ft_strjoin(tmp, list->args[0]);
		free(tmp);
		if (access(full_cmd, X_OK) == 0)
			return (execute_cmd(list, full_cmd));
		free(full_cmd);
		i++;
	}
	ft_free(paths);
	return (1);
}
