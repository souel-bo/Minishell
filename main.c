/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/28 03:22:53 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void print(t_token *list)
{
    while (list)
    {
        printf("%s\n", list->token);
        list = list->next;
    }
}

int main(int argc, char **argv, char **envirement)
{
       (void)argc;
       (void)argv;
       char *input;
       t_token *tokens =NULL;
       while (1)
       {
            input = readline("minishell $>: ");
            if (!input)
                exit(1);
            tokens = tokenizer(input, tokens);
            print(tokens);
            ft_lstclear(&tokens, free);
            free(input);
       }
}