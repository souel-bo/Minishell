/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsUtils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:32 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 23:11:11 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	check_builtin(t_execution *list, int size)
{
	g_status()->stdout_copy = dup(1);
	g_status()->stdin_copy = dup(0);
	if (list)
	{
		if (list->file)
		{
			if (ft_redirection(list->file) == 0)
			{
				is_builtin(list->args[0], list, size);
				dup2(g_status()->stdout_copy, 1);
				dup2(g_status()->stdin_copy, 0);
			}
		}
		else
			is_builtin(list->args[0], list, size);
	}
	close(g_status()->stdin_copy);
	close(g_status()->stdout_copy);
}

int	check_sen(char *list)
{
	int	j;

	j = 0;
	if ((list[0] != '_') && (!ft_isalpha(list[0])))
		return (0);
	while (list[j] && list[j] != '=')
	{
		if (list[j] == '+' && list[j + 1] == '=')
		{
			j++;
			return (1);
		}
		if ((ft_isalnum(list[j]) == 0) && list[j] != '=')
		{
			return (0);
		}
		j++;
	}
	return (1);
}

char	*appand_add(char *line, char *value, int len_key)
{
	if (line[len_key] == '=')
	{
		if (line[len_key + 1] != '\0')
			value = ft_strdup(line + len_key + 1);
		else
			value = ft_strdup("");
	}
	if (line[len_key] == '+')
	{
		if (line[len_key + 2] != '\0')
			value = ft_strdup(line + len_key + 2);
		else
			value = ft_strdup("");
	}
	return (value);
}

t_envp	*new_element2(char *line)
{
	char	*key;
	t_envp	*new;
	int		len_key;
	char	*value;

	if (!line)
		return (NULL);
	len_key = countlenkey(line);
	key = ft_strndup(line, len_key);
	value = NULL;
	if ((line[len_key] == '=') || (line[len_key] == '+'))
		value = appand_add(line, value, len_key);
	new = malloc(sizeof(t_envp));
	if (!new)
	{
		free(key);
		free(value);
		return (NULL);
	}
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	is_builtin(char *cmd, t_execution *list, int size)
{
	if (!ft_strcmp(cmd, "export"))
		ft_export(list);
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(list);
	if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	if (!ft_strcmp(cmd, "env"))
		ft_env();
	if (!ft_strcmp(cmd, "echo"))
		ft_echo(list);
	if (!ft_strcmp(cmd, "cd"))
		ft_chdir(list);
	if (!ft_strcmp(cmd, "exit"))
		ft_exit(list, size);
}
