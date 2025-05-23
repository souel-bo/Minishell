/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_value_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:46:27 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 15:47:44 by souel-bo         ###   ########.fr       */
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
