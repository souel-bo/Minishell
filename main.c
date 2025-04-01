/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/29 05:07:59 by souel-bo         ###   ########.fr       */
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

int check_space(char *input)
{
    int i = 0;
    while (input[i] && (input[i] == ' ' || input[i] == '\t'))
          i++;
    if (input[i] == '\0')
        return 1;
    return 0;
}

int main(int argc, char **argv, char **envirement)
{
       (void)argc;
       (void)argv;
        (void)envirement;
       char *input;
       t_token *tokens =NULL;
       while (1)
       {
            input = readline("minishell $>: ");
            if (!input)
                exit(1);
            if (input)
            {
              if (check_space(input))
              {
                  free(input);
                  input = readline("minishell $>: ");
                  if (!input)
                    exit(1);
              }
              add_history(input);
              tokens = tokenizer(input, tokens);
              print(tokens);
              ft_lstclear(&tokens, free);
              free(input);
            }
        }
}
