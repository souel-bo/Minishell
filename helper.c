/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:50:25 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/22 00:01:25 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "LIBFT/libft.h"
#include "minishell.h"


void	ft_free_split(char **split)
{
	size_t	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
int	count_2D(char **envp)
{
	int i;
	i = 0;
	while(envp[i])
		i++;
	return (i);
}


int	is_builtin(char *cmd, char **envp, t_global *input)
{
	if (!ft_strncmp(cmd, "echo", 4))
		ft_echo(input);
	if (!ft_strncmp(cmd, "cd", 2))
		ft_chdir(input);
	if (!ft_strncmp(cmd, "exit", 4))
		ft_exit(input);
	if (!ft_strncmp(cmd, "pwd", 3))
		ft_pwd();
	if (!ft_strncmp(cmd, "env", 3))
		ft_env(envp);	
	if (!ft_strncmp(cmd, "export", 6) || !ft_strncmp(cmd, "unset", 5))
		ft_export_unset(input, &envp);
	return (0);
}
