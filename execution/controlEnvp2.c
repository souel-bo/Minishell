/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controlEnvp2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:47 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/22 20:21:36 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

t_envp	*ft_create_envp(char **envp)
{
	t_envp	*head;
	t_envp	*node;
	t_envp	*tmp;

	head = NULL;
	if (!envp)
		return (NULL);
	while (*envp)
	{
		node = new_element2(*envp);
		if (!node)
		{
			while (head)
			{
				tmp = head->next;
				free(head);
				head = tmp;
			}
			return (NULL);
		}
		ft_lstadd_back2(&head, node);
		envp++;
	}
	return (head);
}

void	ft_lstadd_back2(t_envp **lst, t_envp *new)
{
	t_envp	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast2(*lst);
		last->next = new;
	}
}

t_envp	*ft_lstlast2(t_envp *lst)
{
	t_envp	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

char	**listtoarray(void)
{
	int		size;
	char	*tmp;
	int		i;
	char	**envpexecve;
	t_envp	*head;

	i = 0;
	size = ft_lstsize_envp(g_status()->new_envp);
	envpexecve = malloc(sizeof(char *) * (size + 1));
	head = g_status()->new_envp;
	while (head)
	{
		tmp = ft_strjoin(head->key, "=");
		envpexecve[i] = ft_strjoin(tmp, head->value);
		i++;
		free(tmp);
		head = head->next;
	}
	envpexecve[i] = NULL;
	return (envpexecve);
}
