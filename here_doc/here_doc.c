/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:10:46 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/16 04:46:59 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_value(char *temp, const char *s, int *j);
int		find_dollar(char *s);
char	*expand_env(char *key);
int		is_special(char c);

int	handle_heredoc(t_norm *norm, t_file *element)
{
	int		fd;
	pid_t	pid;
	char	*here_doc;
	int		i;
	int		j;
	char	*temp;
	int		n;
	char	*l;
	char	*s;
	int		k;

	i = 0;
	j = 0;
	fd = open("/tmp/minishell", O_RDWR | O_TRUNC | O_CREAT, 0777);
	if (fd == -1)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		while (1)
		{
			here_doc = readline("heredoc-> ");
			if (!here_doc)
			{
				ft_putstr_fd("minishell: warning: here-document at line 1 delimited by end-of-file (wanted `",
					2);
				ft_putstr_fd(norm->token->token, 2);
				ft_putstr_fd("')\n", 2);
				ft_lstclear(&norm->tokens, free);
				if (norm->exec_list)
					ft_lstclear_v2(&norm->exec_list);
				free(norm->ex->file);
				free(element);
				if (norm->ex->args)
				{
					i = 0;
					while (norm->ex->args[i])
						free(norm->ex->args[i++]);
					free(norm->ex->args);
				}
				free(norm->ex);
				ft_freeEnvp();
				close(fd);
				exit(0);
			}
			if (ft_strlen(here_doc) == ft_strlen(norm->token->token)
			&& !ft_strncmp(here_doc, norm->token->token,
				ft_strlen(norm->token->token)))
		{
			free(here_doc);
			break ;
		}
			if (!norm->token->heredoc && find_dollar(here_doc))
			{
				i = 0;
				j = 0;
				temp = malloc(ALLOC);
				if (!temp)
					exit(1);
				while (here_doc[i])
				{
					if (here_doc[i] == '$')
					{
						if (!here_doc[i + 1] || here_doc[i + 1] == '$'
							|| (!ft_is_alpha(here_doc[i + 1]) && here_doc[i
								+ 1] != '?' && here_doc[i + 1] != '_'
								&& here_doc[i + 1] != '\'' && here_doc[i
								+ 1] != '"' && !ft_isdigit(here_doc[i])))
						{
							temp[j++] = here_doc[i++];
						}
						else
						{
							i++;
							if (here_doc[i] >= '0' && here_doc[i] <= '9')
							{
								i++;
								continue ;
							}
							s = malloc(ft_strlen(&here_doc[i]) + 1);
							if (!s)
								exit(1); // or handle malloc error
							k = 0;
							if (here_doc[i] == '?')
							{
								i++;
								l = ft_itoa(g_status()->status);
								n = 0;
								while (l[n])
									temp[j++] = l[n++];
								free(l);
							}
							else
							{
								while (here_doc[i] && (ft_is_alpha(here_doc[i])
										|| here_doc[i] == '_')
									&& !is_special(here_doc[i]))
									s[k++] = here_doc[i++];
							}
							s[k] = '\0';
							s = expand_env(s);
							if (s)
							{
								join_value(temp, s, &j);
								free(s);
							}
						}
					}
					else
					{
						temp[j++] = here_doc[i++];
					}
				}
				free(here_doc);
				here_doc = ft_strndup(temp, ft_strlen(temp));
				free(temp);
			}

			ft_putstr_fd(here_doc, fd);
			ft_putchar_fd('\n', fd);
			free(here_doc);
		}
		ft_lstclear(&norm->tokens, free);
		if (norm->exec_list)
			ft_lstclear_v2(&norm->exec_list);
		free(norm->ex->file);
		free(norm->ex);
		ft_freeEnvp();
		close(fd);
		exit(0);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	return (fd);
}
