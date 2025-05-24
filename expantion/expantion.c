/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:00:24 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 18:01:48 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

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
