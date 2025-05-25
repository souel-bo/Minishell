/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 16:34:31 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 16:35:03 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

void	join_value(char *temp, const char *s, int *j)
{
	int	i;

	i = 0;
	while (s[i])
		temp[(*j)++] = s[i++];
	temp[*j] = '\0';
}

int	check_quote(char *delimiter)
{
	int	i;

	i = 0;
	while (delimiter[i])
	{
		if (delimiter[i] == DOUBLE_QUOTE || delimiter[i] == SINGLE_QUOTE)
			return (1);
		else
			i++;
	}
	return (0);
}

void	set_quote(t_token *new)
{
	if (new->type == DELIMITER)
	{
		if (check_quote(new->token))
			new->heredoc = 1;
		else
			new->heredoc = 0;
	}
}

t_token	*join_token(t_token *token)
{
	t_token(*iterate) = NULL;
	t_token(*next) = NULL;
	t_token(*new) = NULL;
	t_token(*list) = NULL;
	iterate = token;
	while (iterate)
	{
		if (iterate->expanded && (iterate->token[0] == '\0'))
		{
			next = iterate->next;
			ft_lstdelone(iterate, free);
			iterate = next;
			continue ;
		}
		new = new_element(iterate->token);
		new->type = iterate->type;
		set_quote(new);
		ft_lstadd_back(&list, new);
		next = iterate->next;
		free(iterate);
		iterate = next;
	}
	return (list);
}

t_token	*expantion(t_token *token)
{
	token = expand_value(token);
	token = join_token(token);
	token = handle_quote(token);
	return (token);
}
