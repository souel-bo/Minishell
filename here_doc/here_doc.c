/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:10:46 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/13 16:18:28 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int handle_heredoc(t_token *token)
{
    int fd;
    pid_t pid;
    char *here_doc;
    
    fd = open("/tmp/minishell", O_RDWR | O_TRUNC | O_CREAT, 0777);
    if (fd == -1)
        printf("test\n");
    pid = fork();
    if (pid == 0)
    {
        while (1)
        {
            here_doc = readline("heredoc-> ");

            if (!ft_strncmp(here_doc, token->token, ft_strlen(token->token)) && ft_strlen(here_doc) == ft_strlen(token->token))
                break;
            free(here_doc);
        }
        exit(0);
    }
    else if (pid > 0)
        wait(NULL);
    return fd;
}