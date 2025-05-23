/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 14:38:28 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/23 15:44:52 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

void	without_argument(void)
{
	char *home;
	if (search_in_env("HOME") == 1)
	{
		change_in_env("OLDPWD", getcwd(NULL, 0));
		home = searchandsave("HOME");
		if (chdir(home) == 0)
		{
			free(home);
			g_status()->status = 0;
			return ;
		}
		change_in_env("PWD", getcwd(NULL, 0));
		g_status()->status = 0;
	}
	else
	{
		printf("%s\n", "cd: HOME not set");
		g_status()->status = 1;
	}
}

void	invalid_argument(t_execution *input)
{
	char *tmp;
	change_in_env("OLDPWD", getcwd(NULL, 0));
	if (chdir(input->args[1]) == -1)
	{
		g_status()->status = 1;
		print_error2("bash: cd: ", input
			->args[1], " :No such file or directory", 1);
		return ;
	}
	tmp = getcwd(NULL, 0);
	change_in_env("PWD", tmp);
	free(tmp);
	g_status()->status = 0;
}

void	ft_chdir(t_execution *input)
{
	int len_args;
	len_args = array_len(input->args);
	if (len_args >= 3)
	{
		print_error(input->args[0], ": too many arguments");
		g_status()->status = 1;
	}
	else if (!input->args[1])
		without_argument();
	else
		invalid_argument(input);
}

void	ft_echo(t_execution *input)
{
	int (j) = 0;
	int (i) = 1;
	int (flag) = 1;
	while (input->args[i] && input->args[i][j] && input->args[i][j] == '-')
	{
		j++;
		while (input->args[i][j] && input->args[i][j] == 'n' )
			j++;
		if (input->args[i][j] == '\0')
		{
			flag = 0;
			j = 0;
			i++;
		}
		else
			break ;
	}
	while (input->args[i])
	{
		ft_putstr_fd(input->args[i], 1);
		if (input->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (flag)
		ft_putchar_fd('\n', 1);
	g_status()->status = 0;
}
