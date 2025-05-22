/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsUtils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aniki <aniki@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:37 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/22 04:08:25 by aniki            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	find_it(int append, t_envp *tmp, char *arg, int len_key)
{
	char	*new_value;

	if (append)
		new_value = ft_strjoin(tmp->value, arg + len_key + 2);
	else
		new_value = ft_strdup(arg + len_key + 1);
	free(tmp->value);
	tmp->value = new_value;
}

int	already_in(char *arg)
{
	char	*key;
	int		len_key;

	int (append) = 0;
	t_envp *(tmp) = g_new_envp;
	len_key = countlenkey(arg);
	if (arg[len_key] == '+' && arg[len_key + 1] == '=')
		append = 1;
	key = ft_strndup(arg, len_key);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, len_key) == 0
			&& tmp->key[len_key] == '\0')
		{
			find_it(append, tmp, arg, len_key);
			return (1);
		}
		tmp = tmp->next;
	}
	free(key);
	return (0);
}

int	if_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

void	unset_var(t_envp *prev, t_envp *current)
{
	if (prev == NULL)
		g_new_envp = current->next;
	else
		prev->next = current->next;
	free(current->key);
	free(current->value);
	free(current);
}

void	export_signle(t_envp *export)
{
	while (export)
	{
		if (export->key && export->value)
			printf("declare -x %s=\"%s\"\n", export->key, export->value);
		else if (export->key)
			printf("declare -x %s\n", export->key);
		export = export->next;
	}
}
