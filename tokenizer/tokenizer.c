/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 02:20:32 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/29 00:25:14 by souel-bo         ###   ########.fr       */
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
	while (input[i])
	{
		while (input[i] && input[i] == ' ')
			i++;
		j = i;
		if (input[i] == '|' || input[i] == '<' || input[i] == '>')
		{
			if (i > j)
			{
				element = new_element(ft_strndup(&input[j], i - j));
				ft_lstadd_back(&tokens, element);
			}
			if (input[i] == '<' && input[i + 1] == '<')
			{
				element = new_element(ft_strndup("<<", 2));
				ft_lstadd_back(&tokens, element);
				i += 2;
			}
			else if (input[i] == '>' && input[i + 1] == '>')
			{
				element = new_element(ft_strndup(">>", 2));
				ft_lstadd_back(&tokens, element);
				i += 2;
			}
			else if (input[i] == '|' && input[i + 1] == '|')
			{
				element = new_element(ft_strndup("||", 2));
				ft_lstadd_back(&tokens, element);
				i += 2;
			}
			else if (input[i] == '&' && input[i + 1] == '&')
			{
				element = new_element(ft_strndup("&&", 2));
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
				&& input[i] != '<' && input[i] != '>')
				i++;
			element = new_element(ft_strndup(&input[j], i - j));
			ft_lstadd_back(&tokens, element);
		}
	}
	return (tokens);
}
