/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:47:59 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 18:13:27 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

void	check_operator(t_token *token)
{
	if (!ft_strncmp(token->token, "|", ft_strlen(token->token)))
		token->type = PIPE;
	else if (!ft_strncmp(token->token, ">>", 2))
	{
		token->type = APPEND;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = FILE_NAME;
		}
	}
	else if (!ft_strncmp(token->token, ">", 1))
	{
		token->type = RED_OUT;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = FILE_NAME;
		}
	}
	else
		check_in(token);
}

void	check_argument(t_token *iteration)
{
	while (iteration != NULL && !check_opperator(iteration->token))
	{
		if (!check_if_operator(iteration))
			iteration->type = ARGUMENT;
		iteration = iteration->next;
	}
}

int	check_if_builtin(t_token *token)
{
	if (!ft_strncmp(token->token, "echo", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "cd", 2))
		return (1);
	else if (!ft_strncmp(token->token, "pwd", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "export", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "unset", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "env", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "exit", ft_strlen(token->token)))
		return (1);
	return (0);
}

void	handle_token(t_token *iter, int *new_cmd)
{
	if (*new_cmd && check_if_builtin(iter))
	{
		iter->type = BUILTIN;
		check_argument(iter->next);
		*new_cmd = 0;
	}
	else if (check_if_operator(iter))
	{
		check_operator(iter);
		if (iter->type == PIPE)
			*new_cmd = 1;
	}
	else
	{
		iter->type = WORD;
		*new_cmd = 0;
	}
}

t_token	*lexer(t_token *list)
{
	t_token	*iter;
	int		new_cmd;

	iter = list;
	new_cmd = 1;
	while (iter)
	{
		if (iter->type == TEST)
			handle_token(iter, &new_cmd);
		iter = iter->next;
	}
	return (list);
}
