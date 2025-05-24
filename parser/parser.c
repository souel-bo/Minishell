/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/05/24 18:44:34 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

void	update_quote_state(char *c, char *quote)
{
	if ((*c == '\'' || *c == '"') && *quote == 0)
	{
		*quote = *c;
		if (*c == '"')
			*c = DOUBLE_QUOTE;
		else
			*c = SINGLE_QUOTE;
	}
	else if (*c == *quote)
	{
		*quote = 0;
		if (*c == '"')
			*c = DOUBLE_QUOTE;
		else
			*c = SINGLE_QUOTE;
	}
}

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		update_quote_state(&input[i], &quote);
		i++;
	}
	if (quote != 0)
	{
		g_status()->status = 2;
		return (1);
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

int	parser(t_token *tokens)
{
	t_token	*iterate;
	int		i;

	i = 0;
	iterate = tokens;
	while (iterate)
	{
		if (iterate->type == PIPE)
		{
			if (check_pipe(iterate, i))
				return (1);
		}
		else if (helper_check(iterate))
			return (1);
		iterate = iterate->next;
		i++;
	}
	return (0);
}
