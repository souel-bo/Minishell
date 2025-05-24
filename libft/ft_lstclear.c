/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniki <aniki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 03:20:47 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 01:56:53 by aniki            ###   ########.fr       */
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
// void	ft_lstclear4(t_file *file)
// {
// 	t_file	*current;
// 	t_file	*next_node;

// 	if (!file)
// 		return ;
// 	current = file;
// 	while (current != NULL)
// 	{
// 		next_node = current->next;
// 		if (current->file_name != NULL)
// 			printf("wselt\n");
// 		// free(current->file_name);
// 		current = next_node;
// 	}
// 	free(file);
// }

void	ft_lstclear_v2(t_execution **lst)
{
	t_execution	*current;
	t_execution	*next_node;
	int i;

	if (!lst || !*lst)
		return ;

	current = *lst;
	while (current != NULL)
	{
		next_node = current->next;
		t_file *file_tmp;
		while (current->file) {
			file_tmp = current->file->next;
			free(current->file->file_name);
			free(current->file);
			current->file = file_tmp;
		}
		i = 0;
		while (current->args && current->args[i]) {
			free(current->args[i]);
			i++;
		}
		free(current->args);
		if (current->infile != -2)
			close(current->infile);
		if (current->outfile != -2)
			close(current->outfile);
		free(current);
		current = next_node;
	}
	*lst = NULL;
}

