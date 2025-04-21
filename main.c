/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/21 21:06:56 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void free_list(t_execution *list)
{
    t_execution *tmp;

    while (list)
    {
        tmp = list->next;
        ft_free(list->args);
        list = tmp;
    }
    free(list);
}
const char *type_to_string(t_type type)
{
    if (type == BUILTIN)
        return "BUILTIN";
    else if (type == PIPE)
        return "PIPE";
    else if (type == RED_IN)
        return "RED_IN";
    else if (type == RED_OUT)
        return "RED_OUT";
    else if (type == FILE_NAME)
        return "FILE_NAME";
	else if (type == HERE_DOC)
        return "HERE_DOC";
	else if (type == DELIMITER)
        return "DELIMITER";
	else if (type == APPEND)
        return "APPEND";
	else if (type == ARGUMENT)
        return "ARGUMENT";
    return "WORD";
}

void print(t_execution *list)
{
    int i;
    while (list)
    {
            i = 0;
            while (list->args[i])
            {
                printf("%s ", list->args[i]);
                i++;
            }   

        printf("\n");
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
       t_token *tokens = NULL;
       t_execution *pre = NULL;
       while (1)
       {
            input = readline("minishell $>: ");
			add_history(input);
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
              tokens = tokenizer(input, tokens);
              pre = pre_execution(tokens);
            //   print(pre);
              ft_execution(pre,envirement);
              ft_lstclear(&tokens, free);
              free(input);
            }
            // free_list(pre);
        }
}
