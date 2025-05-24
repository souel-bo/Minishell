/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 12:13:17 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 15:26:34 by souel-bo         ###   ########.fr       */
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

char	*expand_here_doc(char *input)
{
	t_norm_v2	obj;

	obj.temp = NULL;
	obj.i = 0;
	obj.s = NULL;
	obj.j = 0;
	obj.k = 0;
	obj.l = NULL;
	obj.n = 0;
	if (find_dollar(input))
	{
		obj.temp = malloc(ALLOC);
		obj.i = 0;
		obj.j = 0;
		while (input[obj.i])
		{
			if (input[obj.i] == '$')
			{
				if (!input[obj.i + 1] || input[obj.i + 1] == '$'
					|| (!ft_is_alpha(input[obj.i + 1]) && input[obj.i
						+ 1] != '?' && input[obj.i + 1] != '_' && input[obj.i
						+ 1] != '\'' && input[obj.i + 1] != '"'
						&& !ft_isdigit(input[obj.i])))
					obj.temp[obj.j++] = input[obj.i++];
				else
				{
					obj.i++;
					if (input[obj.i] >= '0' && input[obj.i] <= '9')
					{
						obj.i++;
						continue ;
					}
					else
					{
						obj.s = malloc(ft_strlen(&input[obj.i]) + 1);
						if (!obj.s)
							return (NULL);
						obj.k = 0;
						if (input[obj.i] == '?')
						{
							obj.i++;
							obj.l = ft_itoa(g_status()->status);
							obj.n = 0;
							while (obj.l[obj.n])
								obj.temp[obj.j++] = obj.l[obj.n++];
							free(obj.l);
						}
						else
						{
							while (input[obj.i] && (ft_is_alpha(input[obj.i])
									|| input[obj.i] == '_')
								&& !is_special(input[obj.i]))
								obj.s[obj.k++] = input[obj.i++];
						}
						obj.s[obj.k] = '\0';
						obj.s = expand_env(obj.s);
						if (obj.s)
						{
							join_value(obj.temp, obj.s, &obj.j);
							free(obj.s);
						}
					}
				}
			}
			else
				obj.temp[obj.j++] = input[obj.i++];
		}
		obj.temp[obj.j] = '\0';
		free(input);
		input = ft_strndup(obj.temp, ft_strlen(obj.temp));
		free(obj.temp);
	}
	return (input);
}

int	read_here_doc(int fd, char *delimiter, int flag, t_token *tokens,
		char *file_nm)
{
	char	*input;
	pid_t	pid;

	pid = fork_here_doc();
	if (pid == 0)
	{
		while (!g_status()->interuppeted)
		{
			input = readline("here_doc $-> : ");
			if (!input)
			{
				if (!g_status()->interuppeted)
				{
					printf("CTRL + D\n");
					ft_lstclear(&tokens, free);
					ft_freeEnvp();
					free(file_nm);
					close(fd);
					exit(0);
				}
				else
				{
					printf("CTRL + C\n");
					ft_lstclear(&tokens, free);
					ft_freeEnvp();
					free(file_nm);
					close(fd);
					exit(g_status()->status);
				}
			}
			else if (ft_strlen(delimiter) == ft_strlen(input)
				&& !ft_strncmp(delimiter, input, ft_strlen(delimiter)))
				break ;
			if (!flag)
				input = expand_here_doc(input);
			ft_putstr_fd(input, fd);
			ft_putchar_fd('\n', fd);
			free(input);
		}
		printf("dkhel hna\n");
		ft_lstclear(&tokens, free);
		ft_freeEnvp();
		free(file_nm);
		free(input);
		close(fd);
		g_status()->status = 0;
		exit(g_status()->status);
	}
	else
	{
		waitpid(pid, &g_status()->status, 0);
		if (WIFEXITED(g_status()->status))
		{
			g_status()->status = WEXITSTATUS(g_status()->status);
			if (g_status()->status == 130)
				return (1);
			return (0);
		}
	}
	return (0);
}

t_token	*handle_heredoc(t_token *tokens)
{
	t_token *iterate;
	char *file_nm;
	int fd;

	iterate = tokens;
	while (iterate)
	{
		while (iterate && iterate->type != HERE_DOC)
			iterate = iterate->next;
		if (iterate && iterate->type == HERE_DOC)
		{
			free(iterate->token);
			iterate->token = ft_strndup("<", 1);
			iterate->type = RED_IN;
			iterate = iterate->next;
			file_nm = file_name();
			fd = open(file_nm, O_CREAT | O_RDWR, 0666);
			if (read_here_doc(fd, iterate->token, iterate->heredoc, tokens,
					file_nm))
			{
				free(file_nm);
				ft_lstclear(&tokens, free);
				close(fd);
				return (NULL);
			}
			free(iterate->token);
			iterate->token = ft_strndup(file_nm, ft_strlen(file_nm));
			iterate->type = FILE_NAME;
			free(file_nm);
			close(fd);
		}
		else
		{
			if (iterate && iterate->next)
				iterate = iterate->next;
		}
	}
	return (tokens);
}