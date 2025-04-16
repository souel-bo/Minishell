/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:20:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/16 21:58:01 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_token **lst, void (*del)(void *))
{
	t_token	*current;
	t_token	*next_node;

	if (!lst || !*lst || !del)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next_node = current->next;
		ft_lstdelone(current, del);
		current = next_node;
	}
	*lst = NULL;
}
