/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:03:08 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 15:49:03 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

void	asign_clean(t_norm_v2 *obj, t_token *iterate)
{
	obj->temp[obj->j] = '\0';
	free(iterate->token);
	iterate->token = ft_strndup(obj->temp, ft_strlen(obj->temp));
	free(obj->temp);
}

void	initialize_value(t_norm_v2 *obj, t_token *iterate)
{
	iterate->expanded = 1;
	obj->i = 0;
	obj->j = 0;
	obj->temp = malloc(ALLOC);
	if (!obj->temp)
		return ;
}

t_token	*expand_value(t_token *token)
{
	t_token		*iterate;
	t_norm_v2	obj;

	iterate = token;
	while (iterate)
	{
		if (find_dollar(iterate->token) && iterate->type != DELIMITER)
		{
			initialize_value(&obj, iterate);
			while (iterate->token[obj.i])
			{
				if (iterate->token[obj.i] == DOUBLE_QUOTE)
					expand_double_quote(&obj, iterate);
				else if (iterate->token[obj.i] == SINGLE_QUOTE)
					expand_single_quote(&obj, iterate);
				else if (iterate->token[obj.i] == '$')
					normal_expand(&obj, iterate);
				else
					obj.temp[obj.j++] = iterate->token[obj.i++];
			}
			asign_clean(&obj, iterate);
		}
		iterate = iterate->next;
	}
	return (token);
}
