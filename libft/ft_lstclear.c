/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:20:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/18 16:34:10 by souel-bo         ###   ########.fr       */
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
void	ft_lstclear_v2(t_execution **lst)
{
	t_execution	*current;
	t_execution	*next_node;
	int i = 0;
	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next_node = current->next;
		i = 0;
		while (current->args[i])
		{
			free(current->args[i]);
			i++;
		}
		free(current->args);
		current = next_node;
	}
	free(*lst);
}
