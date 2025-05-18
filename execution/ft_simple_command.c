/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:06 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/17 16:14:09 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	ft_open(char *file_name, int flag)
{
	int	fd;

	fd = open(file_name, flag, 0644);
	if (fd < 0)
	{
		perror(file_name);
		g_status()->status = 1;
		return (-2);
	}
	return (fd);
}

int	ft_redirection(t_execution *file)
{
	int	fd = -2;

	while (file->file)
	{
		if (file->file->outfile)
		{
			fd = ft_open(file->file->file_name, O_CREAT | O_TRUNC | O_WRONLY);
			if (fd != -2)
			{
				dup2(fd, 1);
				close(fd);
			}
		}
		if (file->file->infile)
		{
			fd = ft_open(file->file->file_name, O_RDONLY);
			if (fd != -2)
			{
				dup2(fd, 0);
				close(fd);
			}
		}
		if (file->file->append)
		{
			fd = ft_open(file->file->file_name, O_APPEND | O_CREAT | O_WRONLY);
			if (fd != -2)
			{
				dup2(fd, 1);
				close(fd);
			}
		}
		file->file = file->file->next;
	}
	return (0);
}
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
char	**get_path(void)
{
	char	*path;
	char	**path_2D;

	path = searchAndsave("PATH");
	if (path)
	{
		path_2D = ft_split(path, ':');
		free(path);
		return (path_2D);
	}
	return (NULL);
}
