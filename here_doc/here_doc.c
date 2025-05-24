/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:13:17 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 21:19:55 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

int	process_heredoc(t_token *here_token, t_token **tokens)
{
	char		*file_nm;
	t_here_doc	here;

	free(here_token->token);
	here_token->token = ft_strndup("<", 1);
	here_token->type = RED_IN;
	here_token = here_token->next;
	file_nm = file_name();
	here.file_nm = file_nm;
	if (read_here_doc(&here, here_token->token, here_token->heredoc, *tokens))
	{
		free(file_nm);
		ft_lstclear(tokens, free);
		return (1);
	}
	free(here_token->token);
	here_token->token = ft_strndup(file_nm, ft_strlen(file_nm));
	here_token->type = FILE_NAME;
	free(file_nm);
	return (0);
}

t_token	*handle_heredoc(t_token *tokens)
{
	t_token	*iterate;

	iterate = tokens;
	while (iterate)
	{
		while (iterate && iterate->type != HERE_DOC)
			iterate = iterate->next;
		if (iterate && iterate->type == HERE_DOC)
		{
			if (process_heredoc(iterate, &tokens))
				return (NULL);
		}
		else if (iterate && iterate->next)
			iterate = iterate->next;
	}
	return (tokens);
}
