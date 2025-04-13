/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/13 21:44:58 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include <string.h> 

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
const char *type_to_string2(t_flag type)
{
    if (type == ITS_PIPE)
        return "ITS_PIPE";
    else if (type == ITS_RED_IN)
        return "ITS_RED_IN";
    else if (type == ITS_RED_OUT)
        return "ITS_RED_OUT";
    else if (type == FILE_NAME)
        return "ITS_FILE_NAME";
	else if (type == HERE_DOC)
        return "ITS_HERE_DOC";
	else if (type == ITS_APPEND)
        return "ITS_APPEND";
    return NULL;
}

void print(t_token *list)
{
    while (list)
    {
        printf("[%s]%s\n", type_to_string(list->type),list->token);
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
       char *input;
       t_new_list *new_list;
       t_token *tokens = NULL;
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
            //   print(tokens);
              new_list = ft_create_list(tokens);
              ft_execution(new_list,envirement);
              ft_lstclear(&tokens, free);
              free(input);
            }
        }
}
