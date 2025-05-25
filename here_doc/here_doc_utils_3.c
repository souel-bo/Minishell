/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:44:15 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 21:17:48 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

void	exit_ctrl_d(t_token *tokens, char *file_nm, int fd)
{
	ft_lstclear(&tokens, free);
	ft_freenvp();
	free(file_nm);
	close(fd);
	exit(0);
}

void	exit_ctrl_c(t_token *tokens, char *file_nm)
{
	ft_lstclear(&tokens, free);
	ft_freenvp();
	free(file_nm);
	exit(g_status()->status);
}

void	exit_normal(t_token *tokens, char *file_nm, int fd, char *input)
{
	ft_lstclear(&tokens, free);
	ft_freenvp();
	free(file_nm);
	free(input);
	close(fd);
	g_status()->status = 0;
	exit(g_status()->status);
}

void	child_here_doc(char *input, t_token *tokens, t_here_doc *here, int flag)
{
	here->buffer = NULL;
	here->tmp = NULL;
	while (!g_status()->interuppeted)
	{
		input = readline("here_doc $-> : ");
		if (!input)
		{
			if (!g_status()->interuppeted)
				help_ctrl_d(tokens, here);
			else
				help_ctrl_c(tokens, here);
		}
		else if (ft_strlen(here->delimiter) == ft_strlen(input)
			&& !ft_strncmp(here->delimiter, input, ft_strlen(here->delimiter)))
			break ;
		if (!flag)
			input = expand_here_doc(input);
		help_normal(input, here);
	}
	here->fd = open(here->file_nm, O_CREAT | O_RDWR, 0666);
	write(here->fd, here->buffer, ft_strlen(here->buffer));
	free(here->buffer);
	exit_normal(tokens, here->file_nm, here->fd, input);
}

int	read_here_doc(t_here_doc *here, char *delimiter, int flag, t_token *tokens)
{
	char	*input;
	pid_t	pid;

	pid = fork_here_doc();
	if (pid == 0)
	{
		input = NULL;
		here->delimiter = delimiter;
		child_here_doc(input, tokens, here, flag);
	}
	else
	{
		waitpid(pid, &g_status()->status, 0);
		if (WIFEXITED(g_status()->status))
		{
			g_status()->status = WEXITSTATUS(g_status()->status);
			if (g_status()->status == 130)
				return (1);
			return (0);
		}
	}
	return (0);
}
