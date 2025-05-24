/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/05/24 18:06:11 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int	check_quotes(char *input)
{
	int	i;
	char quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '"') && quote == 0)
		{
			quote = input[i];
			if (input[i] == '"')
				input[i] = DOUBLE_QUOTE;
			else 
				input[i] = SINGLE_QUOTE;
		}
		else if (input[i] == quote)
		{
			quote = 0;
			if (input[i] == '"')
				input[i] = DOUBLE_QUOTE;
			else 
				input[i] = SINGLE_QUOTE;
		}
		i++;
	}
	if (quote != 0)
	{
		g_status()->status = 2;
		return 1;
	}
	return (0);
}

int	parser(t_token *tokens)
{
	t_token	*iterate;
	int i;

	i = 0;
	iterate = tokens;
	while (iterate)
	{
		if (iterate->type == PIPE)
		{
			if (!iterate->next || iterate->next->type == PIPE || (i == 0 && iterate->type == PIPE))
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
				g_status()->status = 2;
				return (1);
			}
		}
		else if (iterate->type == HERE_DOC)
		{
			if (!iterate->next || iterate->next->type != DELIMITER)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				g_status()->status = 2;
				return (1);
			}
		}
		else if (iterate->type == RED_IN || iterate->type == RED_OUT || iterate->type == APPEND)
		{
			if (!iterate->next || iterate->next->type != FILE_NAME)
			{
				ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
				g_status()->status = 2;
				return (1);
			}
		}
		iterate = iterate->next;
		i++;
	}
	return (0);
}

int	count_words(t_token *tokens)
{
	t_token	*iterator;
	int		i;

	iterator = tokens;
	i = 0;
	while (iterator)
	{
		if (iterator->type == PIPE)
			break ;
		i++;
		iterator = iterator->next;
	}
	return (i);
}

t_execution	*create_element(t_token *tokens)
{
	t_execution	*element;
	int			i;

	element = malloc(sizeof(t_execution));
	if (!element)
		return (NULL);
	element->args = malloc(sizeof(char *) * (count_words(tokens) + 1));
	if (!element->args)
	{
		free(element);
		return (NULL);
	}
	i = 0;
	while (i <= count_words(tokens))
		element->args[i++] = NULL;
	element->infile = -2;
	element->outfile = -2;
	element->file = NULL;
	element->next = NULL;
	return (element);
}
