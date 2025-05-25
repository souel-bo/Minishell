/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:42:23 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 17:42:54 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "here_doc.h"

char	*file_name(void)
{
	static int	i = 0;
	char		*join;
	char		*it;

	it = NULL;
	join = NULL;
	it = ft_itoa(i);
	join = ft_strjoin(HERE_DOC_FILE, it);
	free(it);
	while (!access(join, F_OK))
	{
		i++;
		it = ft_itoa(i);
		free(join);
		join = ft_strjoin(HERE_DOC_FILE, it);
		free(it);
	}
	return (join);
}

void	here_doc_handler(int i)
{
	(void)i;
	g_status()->status = 130;
	g_status()->interuppeted = 1;
	write(2, "\n", 1);
	close(STDIN_FILENO);
}

pid_t	fork_here_doc(void)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		signal(SIGINT, here_doc_handler);
	return (pid);
}

int	copy_character(char *input, t_norm_v2 *obj)
{
	if (!input[obj->i + 1] || input[obj->i + 1] == '$'
		|| (!ft_is_alpha(input[obj->i + 1]) && input[obj->i + 1] != '?'
			&& input[obj->i + 1] != '_' && input[obj->i + 1] != '\''
			&& input[obj->i + 1] != '"' && !ft_isdigit(input[obj->i])))
		return (1);
	return (0);
}

void	copy_variables_here(char *input, t_norm_v2 *obj)
{
	while (input[obj->i] && (ft_is_alpha(input[obj->i]) || input[obj->i] == '_')
		&& !is_special(input[obj->i]))
		obj->s[obj->k++] = input[obj->i++];
}
