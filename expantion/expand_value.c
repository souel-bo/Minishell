/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:03:08 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 15:21:09 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/expantion.h"

void	expand_exit_status(t_norm_v2 *obj)
{
	obj->i++;
	obj->l = ft_itoa(g_status()->status);
	obj->n = 0;
	while (obj->l[obj->n])
		obj->temp[obj->j++] = obj->l[obj->n++];
	free(obj->l);
}

void	expand_single_quote(t_norm_v2 *obj, t_token *iterate)
{
	obj->temp[obj->j++] = iterate->token[obj->i++];
	while (iterate->token[obj->i] && iterate->token[obj->i] != SINGLE_QUOTE)
		obj->temp[obj->j++] = iterate->token[obj->i++];
	if (iterate->token[obj->i] == SINGLE_QUOTE)
		obj->temp[obj->j++] = iterate->token[obj->i++];
}

int	check(t_norm_v2 *obj, t_token *iterate)
{
	if (!iterate->token[obj->i + 1] || iterate->token[obj->i + 1] == '$'
		|| (!ft_is_alpha(iterate->token[obj->i + 1]) && iterate->token[obj->i
				+ 1] != '?' && iterate->token[obj->i + 1] != '_'
			&& iterate->token[obj->i + 1] != SINGLE_QUOTE
			&& iterate->token[obj->i + 1] != DOUBLE_QUOTE
			&& !ft_isdigit(iterate->token[obj->i])))
		return (1);
	return (0);
}

int	check_2(t_norm_v2 *obj, t_token *iterate)
{
	if (iterate->token[obj->i + 1] == DOUBLE_QUOTE || !iterate->token[obj->i
			+ 1] || iterate->token[obj->i + 1] == '$'
		|| (!ft_is_alpha(iterate->token[obj->i + 1]) && iterate->token[obj->i
				+ 1] != '?' && iterate->token[obj->i + 1] != '_'))
		return (1);
	return (0);
}

void	copy_variable(t_norm_v2 *obj, t_token *iterate)
{
	while (iterate->token[obj->i] && (ft_is_alpha(iterate->token[obj->i])
			|| iterate->token[obj->i] == '_')
		&& !is_special(iterate->token[obj->i]))
		obj->s[obj->k++] = iterate->token[obj->i++];
}

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
