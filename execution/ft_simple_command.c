/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:06 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/13 15:27:36 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	ft_open(char *file_name, int flag)
{
	int	fd;

	fd = open(file_name, flag, 0644);
	return (fd);
}

int	ft_redirection(t_file *file)
{
	int	fd;

	while (file)
	{
		if (file->infile)
		{
			fd = ft_open(file->file_name, O_RDONLY);
			if (fd == -1)
			{
				write(2, file->file_name, ft_strlen(file->file_name));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				g_status()->status = 1;
				return (1);
			}
			dup2(fd, 0);
			close(fd);
		}
		if (file->outfile)
		{
			fd = ft_open(file->file_name, O_CREAT | O_TRUNC | O_WRONLY);
			if (fd == -1)
			{
				write(2, file->file_name, ft_strlen(file->file_name));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				g_status()->status = 1;
				return (1);
			}
			dup2(fd, 1);
			close(fd);
		}
		if (file->append)
		{
			fd = ft_open(file->file_name, O_APPEND | O_CREAT | O_WRONLY);
			if (fd == -1)
			{
				write(2, file->file_name, ft_strlen(file->file_name));
				write(2, ": ", 2);
				write(2, strerror(errno), ft_strlen(strerror(errno)));
				write(2, "\n", 1);
				g_status()->status = 1;
				return (1);
			}
			dup2(fd, 1);
			close(fd);
		}
		file = file->next;
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
