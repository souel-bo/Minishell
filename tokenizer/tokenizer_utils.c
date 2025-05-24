/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:27:58 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 18:12:20 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	is_space_or_operator(char c)
{
	return (c == ' ' || c == '\t' || c == '|' || c == '<' || c == '>');
}

int	check_opperator(char *token)
{
	if (!ft_strncmp(token, "|", ft_strlen(token)))
		return (1);
	return (0);
}

int	check_if_operator(t_token *token)
{
	if (!ft_strncmp(token->token, "|", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, ">>", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "<", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, "<<", ft_strlen(token->token)))
		return (1);
	else if (!ft_strncmp(token->token, ">", ft_strlen(token->token)))
		return (1);
	return (0);
}

void	check_in(t_token *token)
{
	if (!ft_strncmp(token->token, "<", ft_strlen(token->token)))
	{
		token->type = RED_IN;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = FILE_NAME;
		}
	}
	else if (!ft_strncmp(token->token, "<<", ft_strlen(token->token)))
	{
		token->type = HERE_DOC;
		if (token->next)
		{
			token = token->next;
			if (!check_if_operator(token))
				token->type = DELIMITER;
		}
	}
}
