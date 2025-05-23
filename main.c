/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 21:53:10 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	ft_freenvp(void)
{
	t_envp	*temp;
	t_envp	*next;

	while (g_status()->new_envp)
	{
		temp = g_status()->new_envp;
		next = temp->next;
		if (temp->key)
			free(temp->key);
		if (temp->value)
			free(temp->value);
		free(temp);
		g_status()->new_envp = next;
	}
}

t_status	*g_status(void)
{
	static t_status	status = {0};

	return (&status);
}

void	handler(int sig)
{
	(void)sig;
	if (g_status()->flag == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_status()->status = 130;
	}
	else
		return ;
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;

	(void)argc;
	(void)argv;
	g_status()->new_envp = NULL;
	g_status()->new_envp = ft_create_envp(envp);
	while (1)
	{
		input = setup_input();
		if (check_quotes(input))
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
			g_status()->status = 2;
			free(input);
			continue ;
		}
		if (start(input))
			continue ;
	}
	ft_freenvp();
}
