/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:20:32 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/12 14:52:10 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

t_token	*tokenizer(char *input, t_token *tokens)
{
	int		i;
	int		j;
	t_token	*element;

  i = 0;
	j = 0;
	if (check_quotes(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		return NULL;
	}
	if (check_parenthis(input))
		return NULL;
	while (input[i])
	{
		while (input[i] && (input[i] == ' ' || input[i] == '\t'))
			i++;
		j = i;
		if (input[i] == '\"')
		{
			i++;
			while (input[i] && input[i] != '\"')
				i++;
			if (input[i] == '\"')
				i++;
			element = new_element(ft_strndup(&input[j], i - j));
			ft_lstadd_back(&tokens, element);
			j = i;
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] && input[i] != '\'')
				i++;
			if (input[i] == '\'')
				i++;
			element = new_element(ft_strndup(&input[j], i - j));
			ft_lstadd_back(&tokens, element);
			j = i;
		}
		else if (input[i] == '(')
		{
			i++;
			while (input[i] && input[i] != ')')
				i++;
			if (input[i] == ')')
				i++;
			element = new_element(ft_strndup(&input[j], i - j));
			ft_lstadd_back(&tokens, element);
			j = i;
		}
		else if (input[i] == '|' || input[i] == '<' || input[i] == '>' || input[i] == '&' || input[i] == '\"')
		{
			if (i > j)
			{
				element = new_element(ft_strndup(&input[j], i - j));
				ft_lstadd_back(&tokens, element);
			}
			if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i + 1] == '>')
			|| (input[i] == '|' && input[i + 1] == '|') || (input[i] == '&' && input[i + 1] == '&'))
			{
				element = new_element(ft_strndup(&input[i], 2));
				ft_lstadd_back(&tokens, element);
				i += 2;
			}
			else
			{
				element = new_element(ft_strndup(&input[i], 1));
				ft_lstadd_back(&tokens, element);
				i++;
			}
			j = i;
		}
		else if (input[i])
		{
			while (input[i] && input[i] != ' ' && input[i] != '|'
				&& input[i] != '<' && input[i] != '>' && input[i] != '&' && input[i] != '\"')
				i++;
			element = new_element(ft_strndup(&input[j], i - j));
			ft_lstadd_back(&tokens, element);
		}
	}
	t_token *test = tokens;
	while (test)
	{
		test->type = TEST;
		test = test->next;
	}
	tokens = lexer(tokens);
	return (tokens);
}
