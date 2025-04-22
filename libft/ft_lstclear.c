/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:20:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/22 14:35:09 by yaaitmou         ###   ########.fr       */
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
		if ((*lst)->infile != -2)
        	close((*lst)->infile);
			
    	if ((*lst)->outfile != -2)
		{
        	close((*lst)->outfile);
		}
		free(current->args);
		current = next_node;
	}
	free(*lst);
}
