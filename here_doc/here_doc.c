/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:10:46 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/14 20:18:43 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_heredoc(t_norm *norm, t_file *element)
{
	int		fd;
	pid_t	pid;
	char	*here_doc;
	int		i;

	i = 0;
	fd = open("/tmp/minishell", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			here_doc = readline("heredoc-> ");
			if (!here_doc)
			{
				ft_lstclear(&norm->tokens, free);
				if (norm->exec_list)
				{
					ft_lstclear_v2(&norm->exec_list);
				}
				free(norm->ex->file);
				free(element);
				if (norm->ex->args)
				{
					i = 0;
					while (norm->ex->args && norm->ex->args[i])
					{
						free(norm->ex->args[i]);
						i++;
					}
					free(norm->ex->args);
				}
				free(norm->ex);
				ft_freeEnvp();
				close(fd);
				exit(1);
			}
			if (ft_strlen(here_doc) == ft_strlen(norm->token->token)
				&& !ft_strncmp(here_doc, norm->token->token,
					ft_strlen(norm->token->token)))
			{
				free(here_doc);
				break ;
			}
			ft_putstr_fd(here_doc, fd);
			ft_putchar_fd('\n', fd);
			free(here_doc);
		}
		ft_lstclear(&norm->tokens, free);
		if (norm->exec_list)
		{
			printf("%s\n", norm->exec_list->args[0]);
			ft_lstclear_v2(&norm->exec_list);
		}
		free(norm->ex->file);
		free(norm->ex);
		ft_freeEnvp();
		close(fd);
		exit(0);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	return (fd);
}
