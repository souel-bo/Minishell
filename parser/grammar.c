/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grammar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:23:42 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 18:24:48 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	help_parser(void)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
		2);
	g_status()->status = 2;
}

int	check_pipe(t_token *iter, int i)
{
	if (!iter->next || iter->next->type == PIPE || (i == 0
			&& iter->type == PIPE))
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		g_status()->status = 2;
		return (1);
	}
	return (0);
}

int	check_heredoc(t_token *iter)
{
	if (!iter->next || iter->next->type != DELIMITER)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd("newline'\n", 2);
		g_status()->status = 2;
		return (1);
	}
	return (0);
}

int	check_redirection(t_token *iter)
{
	if (!iter->next || iter->next->type != FILE_NAME)
	{
		help_parser();
		return (1);
	}
	return (0);
}

int	helper_check(t_token *iterate)
{
	if (iterate->type == HERE_DOC)
	{
		if (check_heredoc(iterate))
			return (1);
	}
	else if (iterate->type == RED_IN || iterate->type == RED_OUT
		|| iterate->type == APPEND)
	{
		if (check_redirection(iterate))
			return (1);
	}
	return (0);
}
