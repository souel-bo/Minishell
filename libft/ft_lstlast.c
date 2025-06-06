/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:04:35 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 17:46:07 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_token	*ft_lstlast(t_token *lst)
{
	t_token	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}
