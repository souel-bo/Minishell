/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qutote_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 18:01:58 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 18:02:13 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

void	double_quote(t_token *iterate, int *i, int *j, char *temp)
{
	(*i)++;
	while (iterate->token[*i] && iterate->token[*i] != DOUBLE_QUOTE)
	{
		temp[(*j)++] = iterate->token[(*i)++];
	}
	if (iterate->token[*i] == DOUBLE_QUOTE)
		(*i)++;
}

void	set_and_clean(t_token **iterate, int *j, char *temp)
{
	temp[*j] = '\0';
	free((*iterate)->token);
	(*iterate)->token = ft_strndup(temp, *j);
	free(temp);
	*iterate = (*iterate)->next;
}

void	single_quote(t_token *iterate, int *i, int *j, char *temp)
{
	(*i)++;
	while (iterate->token[*i] && iterate->token[*i] != SINGLE_QUOTE)
		temp[(*j)++] = iterate->token[(*i)++];
	if (iterate->token[(*i)] == SINGLE_QUOTE)
		(*i)++;
}

t_token	*handle_quote(t_token *tokens)
{
	t_token	*iterate;
	char	*temp;

	iterate = tokens;
	int (i), (j);
	while (iterate)
	{
		i = 0;
		j = 0;
		temp = malloc(ft_strlen(iterate->token) + 1);
		if (!temp)
			return (NULL);
		while (iterate->token[i])
		{
			if (iterate->token[i] == DOUBLE_QUOTE)
				double_quote(iterate, &i, &j, temp);
			else if (iterate->token[i] == SINGLE_QUOTE)
				single_quote(iterate, &i, &j, temp);
			else
				temp[j++] = iterate->token[i++];
		}
		set_and_clean(&iterate, &j, temp);
	}
	return (tokens);
}
