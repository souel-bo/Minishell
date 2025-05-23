/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainHelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 20:33:54 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/23 23:27:26 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	start(char	*input)
{
	t_token		*tokens = NULL;
	t_execution	*pre = NULL;

	tokens = tokenizer(input, tokens);
	if (parser(tokens))
		ft_lstclear(&tokens, free);
	tokens = handle_heredoc(tokens);
	if (!tokens)
	{
		ft_lstclear(&tokens, free);
		free(input);
		return (1);
	}
	tokens = expantion(tokens);
	pre = pre_execution(tokens);
	ft_lstclear(&tokens, free);
	check_command_type(pre);
	ft_lstclear_v2(&pre);
	free(input);
	return 0;
}

char	*setup_input(void)
{
	char	*input;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	g_status()->flag = 0;
	input = readline("minishell $>: ");
	if (!input)
	{
		if (isatty(STDIN_FILENO))
			write(2, "exit", 4);
		ft_freenvp();
		exit(g_status()->status);
	}
	add_history(input);
	g_status()->flag = 1;
	return(input);
}
const char	*type_to_string(t_type type)
{
	if (type == BUILTIN)
		return ("BUILTIN");
	else if (type == PIPE)
		return ("PIPE");
	else if (type == RED_IN)
		return ("RED_IN");
	else if (type == RED_OUT)
		return ("RED_OUT");
	else if (type == FILE_NAME)
		return ("FILE_NAME");
	else if (type == HERE_DOC)
		return ("HERE_DOC");
	else if (type == DELIMITER)
		return ("DELIMITER");
	else if (type == APPEND)
		return ("APPEND");
	else if (type == ARGUMENT)
		return ("ARGUMENT");
	return ("WORD");
}


