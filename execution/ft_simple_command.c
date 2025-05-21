/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_simple_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:39:06 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/20 15:32:36 by yaaitmou         ###   ########.fr       */
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
		return (-1);
	}
	return (fd);
}

int	ft_redirection(t_file *file)
{
	int (check) = -1;
	while (file)
	{
		if (file->outfile)
		{
			check = ft_open(file->file_name, O_CREAT | O_TRUNC | O_WRONLY);
			if (check == -1)
				return (1);
			dup2(check, STDOUT_FILENO);
			close(check);
		}
		if (file->infile)
		{
			check = ft_open(file->file_name, O_RDONLY);
			if (check == -1)
				return (1);
			dup2(check, STDIN_FILENO);
			close(check);
		} // https://www.ubuy.ma/en/product/1DFDBTKY-cs03xl-laptop-battery-for-hp-elitebook-840-g3-848-g3-850-g3-755-g3-745-g3-elitebook-840-g4-848-g4-85
		if (file->append)
		{
			check = ft_open(file->file_name, O_CREAT | O_APPEND | O_WRONLY);
			if (check == -1)
				return (1);
			dup2(check, STDOUT_FILENO);
			close(check);
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

	path = searchandsave("PATH");
	if (path)
	{
		path_2D = ft_split(path, ':');
		free(path);
		return (path_2D);
	}
	return (NULL);
}
