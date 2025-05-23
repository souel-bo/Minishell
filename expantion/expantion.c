/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:00:24 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 13:03:35 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

t_token	*handle_quote(t_token *tokens)
{
	t_token	*iterate;
	char	*temp;

	iterate = tokens;
	int i, j;
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
			{
				i++;
				while (iterate->token[i] && iterate->token[i] != DOUBLE_QUOTE)
				{
					temp[j] = iterate->token[i];
					j++;
					i++;
				}
				if (iterate->token[i] == DOUBLE_QUOTE)
					i++;
			}
			else if (iterate->token[i] == SINGLE_QUOTE)
			{
				i++;
				while (iterate->token[i] && iterate->token[i] != SINGLE_QUOTE)
				{
					temp[j] = iterate->token[i];
					j++;
					i++;
				}
				if (iterate->token[i] == SINGLE_QUOTE)
					i++;
			}
			else
			{
				temp[j] = iterate->token[i];
				j++;
				i++;
			}
		}
		temp[j] = '\0';
		free(iterate->token);
		iterate->token = ft_strndup(temp, j);
		free(temp);
		iterate = iterate->next;
	}
	return (tokens);
}

int	find_dollar(char *s)
{
	while (*s)
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

int	is_special(char c)
{
	return ((c == '$' || c == DOUBLE_QUOTE));
}

char	*expand_env(char *key)
{
	t_envp	*iterate;

	iterate = g_new_envp;
	while (iterate)
	{
		if (ft_strlen(key) == ft_strlen(iterate->key) && ft_strncmp(key,
				iterate->key, ft_strlen(key)) == 0)
		{
			free(key);
			key = ft_strndup(iterate->value, ft_strlen(iterate->value));
			return (key);
		}
		else
			iterate = iterate->next;
	}
	free(key);
	return (NULL);
}

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
