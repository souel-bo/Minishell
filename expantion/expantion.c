/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:00:24 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/03 17:53:00 by souel-bo         ###   ########.fr       */
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
			if (iterate->token[i] == '"')
			{
				i++;
				while (iterate->token[i] && iterate->token[i] != '"')
				{
					temp[j] = iterate->token[i];
					j++;
					i++;
				}
				if (iterate->token[i] == '"')
					i++;
			}
			else if (iterate->token[i] == '\'')
			{
				i++;
				while (iterate->token[i] && iterate->token[i] != '\'')
				{
					temp[j] = iterate->token[i];
					j++;
					i++;
				}
				if (iterate->token[i] == '\'')
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

t_token	*expand_wildcard(t_token *token)
{
	t_token	*iterate;
	int		i;

	iterate = token;
	while (iterate)
	{
		i = 0;
		while (iterate->token[i])
		{
			if (iterate->token[i] == '*')
			{
				iterate->index = 1;
				break ;
			}
			i++;
		}
		iterate = iterate->next;
	}
	iterate = token;
	return (token);
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

t_token	*expand_value(t_token *token, t_envp *env)
{
	t_token	*iterate;
	int		i;
	int		j;
	char	*temp;

	iterate = token;
	(void)env;
	i = 0;
	j = 0;
	// int k = 0;
	while (iterate)
	{
		temp = malloc(ft_strlen(iterate->token) + 1);
		// char *s = malloc(ft_strlen(iterate->token) + 1);
		i = 0;
		j = 0;
		while (iterate->token[i] )
		{

		}
		free(temp);
		// free(s);
		iterate = iterate->next;
	}
	return (token);
}

t_token	*expantion(t_token *token, t_envp *env)
{
	// (void)env;
	token = expand_value(token, env);
	token = expand_wildcard(token);
	token = handle_quote(token);
	return (token);
}