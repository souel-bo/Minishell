/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value_utils_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:49:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 15:49:34 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

void	normal_expand(t_norm_v2 *obj, t_token *iterate)
{
	if (check(obj, iterate))
		obj->temp[obj->j++] = iterate->token[obj->i++];
	else
	{
		obj->i++;
		if (iterate->token[obj->i] >= '0' && iterate->token[obj->i] <= '9')
			obj->i++;
		else
		{
			obj->s = malloc(ft_strlen(&iterate->token[obj->i]) + 1);
			if (!obj->s)
				return ;
			obj->k = 0;
			if (iterate->token[obj->i] == '?')
				expand_exit_status(obj);
			else
				copy_variable(obj, iterate);
			obj->s[obj->k] = '\0';
			obj->s = expand_env(obj->s);
			if (obj->s)
				(join_value(obj->temp, obj->s, &obj->j), free(obj->s));
		}
	}
}

void	finish_it(t_norm_v2 *obj)
{
	obj->s[obj->k] = '\0';
	obj->s = expand_env(obj->s);
	if (obj->s)
		(join_value(obj->temp, obj->s, &obj->j), free(obj->s));
}

void	skip(t_norm_v2 *obj, t_token *iterate)
{
	obj->i++;
	if (iterate->token[obj->i] >= '0' && iterate->token[obj->i] <= '9')
		obj->i++;
}

void	helper(t_norm_v2 *obj, t_token *iterate)
{
	if (check_2(obj, iterate))
		obj->temp[obj->j++] = iterate->token[obj->i++];
	else
	{
		skip(obj, iterate);
		obj->s = malloc(ft_strlen(&iterate->token[obj->i]) + 1);
		if (!obj->s)
			return ;
		obj->k = 0;
		if (iterate->token[obj->i] == '?')
			expand_exit_status(obj);
		else
			copy_variable(obj, iterate);
		finish_it(obj);
	}
}

void	expand_double_quote(t_norm_v2 *obj, t_token *iterate)
{
	obj->temp[obj->j++] = iterate->token[obj->i++];
	while (iterate->token[obj->i] && iterate->token[obj->i] != DOUBLE_QUOTE)
	{
		if (iterate->token[obj->i] == '$')
			helper(obj, iterate);
		else
			obj->temp[obj->j++] = iterate->token[obj->i++];
	}
	if (iterate->token[obj->i] == DOUBLE_QUOTE)
		obj->temp[obj->j++] = iterate->token[obj->i++];
}
