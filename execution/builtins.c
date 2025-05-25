/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:23 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 23:14:12 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	ft_env(void)
{
	t_envp	*tmp;

	tmp = g_status()->new_envp;
	while (tmp)
	{
		if (tmp->key && tmp->value && tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_status()->status = 0;
}

void	ft_export(t_execution *list)
{
	t_envp (*node);
	t_envp (*export);
	int (i) = 1;
	export = g_status()->new_envp;
	while (list->args[i])
	{
		if (check_sen(list->args[i]) == 0)
		{
			print_error2("bash: export:", list->args[i],
				": not a valid identifier", 2);
			g_status()->status = 1;
			i++;
		}
		else if (already_in(list->args[i]) == 1)
			i++;
		else
		{
			node = new_element2(list->args[i]);
			ft_lstadd_back2(&g_status()->new_envp, node);
			i++;
			g_status()->status = 0;
		}
	}
	if (!list->args[1])
		export_signle(export);
}

void	ft_unset(t_execution *list)
{
	t_envp	*prev;
	t_envp	*current;

	prev = NULL;
	int (i) = 1;
	while (list->args[i])
	{
		current = g_status()->new_envp;
		prev = NULL;
		while (current)
		{
			if (!ft_strncmp(list->args[i], current->key,
					ft_strlen(list->args[i]))
				&& current->key[ft_strlen(list->args[i])] == '\0')
			{
				unset_var(prev, current);
				break ;
			}
			prev = current;
			current = current->next;
		}
		i++;
	}
	g_status()->status = 0;
}

void	ft_exit(t_execution *input, int size)
{
	int	len_args;

	len_args = array_len(input->args);
	if (size == 1 && len_args == 1)
	{
		write(2, "exit\n", 5);
		free_after_exit();
	}
	else if (input->args[1] && checkifnum(input->args[1]) == 0)
		num_error(input, size);
	else if (len_args >= 3)
	{
		print_error("bash: exit:", "too many arguments");
		g_status()->status = 1;
	}
	else if (input->args[1])
		check_number(input, size);
	else
	{
		ft_lstclear_v2(&g_status()->original_list);
		ft_freenvp();
		free_and_exit();
	}
}

void	ft_pwd(void)
{
	char	*mypwd;
	char	*buf;

	mypwd = searchandsave("PWD");
	buf = getcwd(NULL, 0);
	if (search_in_env("PWD"))
		printf("%s\n", mypwd);
	else
	{
		free (buf);
		return ;
	}
	free(buf);
	free(mypwd);
	g_status()->status = 0;
}
