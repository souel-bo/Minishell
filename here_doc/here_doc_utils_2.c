/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:43:15 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 17:43:42 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

void	expand_value_here_doc(char *input, t_norm_v2 *obj)
{
	obj->s = malloc(ft_strlen(&input[obj->i]) + 1);
	if (!obj->s)
		return ;
	obj->k = 0;
	if (input[obj->i] == '?')
		expand_exit_status(obj);
	else
		copy_variables_here(input, obj);
	obj->s[obj->k] = '\0';
	obj->s = expand_env(obj->s);
	if (obj->s)
		(join_value(obj->temp, obj->s, &obj->j), free(obj->s));
}

void	initialize_obj(t_norm_v2 *obj)
{
	obj->temp = NULL;
	obj->i = 0;
	obj->s = NULL;
	obj->j = 0;
	obj->k = 0;
	obj->l = NULL;
	obj->n = 0;
}

void	expand(char *input, t_norm_v2 *obj)
{
	obj->i++;
	if (input[obj->i] >= '0' && input[obj->i] <= '9')
		obj->i++;
	else
		expand_value_here_doc(input, obj);
}

char	*clean_and_replace(char *input, t_norm_v2 *obj)
{
	char	*new_input;

	obj->temp[obj->j] = '\0';
	free(input);
	new_input = ft_strndup(obj->temp, ft_strlen(obj->temp));
	free(obj->temp);
	return (new_input);
}

char	*expand_here_doc(char *input)
{
	t_norm_v2	obj;

	initialize_obj(&obj);
	if (find_dollar(input))
	{
		obj.temp = malloc(ALLOC);
		obj.i = 0;
		obj.j = 0;
		while (input[obj.i])
		{
			if (input[obj.i] == '$')
			{
				if (copy_character(input, &obj))
					obj.temp[obj.j++] = input[obj.i++];
				else
					expand(input, &obj);
			}
			else
				obj.temp[obj.j++] = input[obj.i++];
		}
		input = clean_and_replace(input, &obj);
	}
	return (input);
}
