/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 21:18:09 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 21:18:25 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"


void	help_normal(char *input, t_here_doc *here)
{
	here->tmp = ft_strjoin_heredoc(here->buffer, input);
	free(here->buffer);
	here->buffer = ft_strjoin_heredoc(here->tmp, "\n");
	free(here->tmp);
	free(input);
}

void	help_ctrl_d(t_token *tokens, t_here_doc *here)
{
	here->fd = open(here->file_nm, O_CREAT | O_RDWR, 0666);
	if (here->buffer)
	{
		write(here->fd, here->buffer, ft_strlen(here->buffer));
		free(here->buffer);
	}
	exit_ctrl_d(tokens, here->file_nm, here->fd);
}

void	help_ctrl_c(t_token *tokens, t_here_doc *here)
{
	if (here->buffer)
		free(here->buffer);
	exit_ctrl_c(tokens, here->file_nm);
}