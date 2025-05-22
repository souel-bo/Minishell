/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmnds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:53 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/22 20:38:36 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	execute_cmd(t_execution *list, char *cmd)
{
	char ** env_char;

	env_char = listtoarray();
	execve(cmd, list->args, env_char);
	free(cmd);
	ft_free(env_char);
	exit(127);
}

void	cmdwithpath(t_execution *list, char **path, int size)
{
	(void)path;
	if (if_builtin(list->args[0]) != 0)
	{
		is_builtin(list->args[0], list, size);
		free(g_status()->pid);
		ft_freeEnvp();
		exit(g_status()->status);
	}
	else if (ft_strchr(list->args[0], '/'))
		scan_cmd(list);
	else if (is_dir(list->args[0]))
	{
		print_error(list->args[0], ": command not found");
		g_status()->status = 127;
		ft_freeEnvp();
		free(g_status()->pid);
		exit(127);
	}
	else if (is_valid(list) == 1)
	{
		g_status()->status = 127;
		print_error(list->args[0], ": command not found");
		ft_freeEnvp();
		free(g_status()->pid);
		exit(127);
	}
}

void	execute_cmds(t_execution *list, t_hr hr, int size)
{
	if (search_in_env("PATH"))
		cmdwithpath(list, hr.path, size);
	else
		scan_cmd(list);
}

void	execute_commands(t_execution *list, t_hr hr, int pipes[2][2], int size)
{
	int (check) = 1;
	if (list->args[0] == NULL && list->file->file_name != NULL)
		check = ft_redirection(list->file);
	if (size == 1 && list->args[0])
	{
		if (list->args[0] == NULL && list->file->file_name != NULL)
		{
			check = ft_redirection(list->file);
			free(g_status()->pid);
			exit(check);
		}
		if (ft_redirection(list->file) == 1)
		{
			free(g_status()->pid);
			exit(1);
		}
		execute_cmds(list, hr, size);
	}
	else if (list->args[0])
		execute_pipeline(pipes, list, hr, size);
	else
		exit(check);
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
