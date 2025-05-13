/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:10:46 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/13 23:27:32 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int handle_heredoc(t_token *token, t_token *tokens, t_execution *exec_list)
{
    int fd;
    pid_t pid;
    char *here_doc;

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
                ft_lstclear(&tokens, free);
                if (exec_list)
                    ft_lstclear_v2(&exec_list);
                exit(1);
            }
            if (ft_strlen(here_doc) == ft_strlen(token->token) && !ft_strncmp(here_doc, token->token, ft_strlen(token->token)))
            {
                free(here_doc);
                break;
            }
            ft_putstr_fd(here_doc, fd);
            ft_putchar_fd('\n', fd);
            free(here_doc);
        }
        close(fd);
        exit(0);
    }
    else if (pid > 0)
    {
        wait(NULL);
    }

    return fd;
}
