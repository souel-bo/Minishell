/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:06 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 23:14:58 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	ft_open(char *file_name, int flag, int in_out)
{
	int	fd;

	fd = open(file_name, flag, 0644);
	if (fd < 0)
	{
		perror(file_name);
		g_status()->status = 1;
		return (-1);
	}
	if (in_out == 1)
		dup2(fd, STDOUT_FILENO);
	else
		dup2(fd, STDIN_FILENO);
	close(fd);
	return (fd);
}

int	ft_redirection(t_file *file)
{
	int (check) = -1;
	while (file)
	{
		if (file->outfile)
		{
			check = ft_open(file->file_name, O_CREAT | O_TRUNC | O_WRONLY, 1);
			if (check == -1)
				return (1);
		}
		if (file->infile)
		{
			check = ft_open(file->file_name, O_RDONLY, 0);
			if (check == -1)
				return (1);
		}
		if (file->append)
		{
			check = ft_open(file->file_name, O_CREAT | O_APPEND | O_WRONLY, 1);
			if (check == -1)
				return (1);
		}
		file = file->next;
	}
	g_status()->status = 0;
	return (0);
}

void	free_after_exit(void)
{
	ft_lstclear_v2(&g_status()->original_list);
	ft_freenvp();
	close(g_status()->stdin_copy);
	close(g_status()->stdout_copy);
	free_and_exit();
}

char	**get_path(void)
{
	char	*path;
	char	**path_2d;

	path = searchandsave("PATH");
	if (path)
	{
		path_2d = ft_split(path, ':');
		free(path);
		return (path_2d);
	}
	return (NULL);
}

void	single_command(t_execution *list, t_hr hr, int size)
{
	if (list->args[0] == NULL && list->file->file_name != NULL)
	{
		redir_free(list);
		free_and_exit();
	}
	if (ft_redirection(list->file) == 1)
	{
		g_status()->status = 1;
		ft_freenvp();
		ft_lstclear_v2(&g_status()->original_list);
		free_and_exit();
	}
	execute_cmds(list, hr, size);
}
