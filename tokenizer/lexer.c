/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 13:47:59 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/10 21:11:41 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int check_opperator(char *token)
{
    if (!ft_strncmp(token, "|", ft_strlen(token)))
        return 1;
    return 0;
}

void check_argument(t_token *iteration)
{
    while (iteration != NULL && !check_opperator(iteration->token))
    {
        iteration->type = ARGUMENT;
        iteration = iteration->next;
    }
}

int check_if_builtin(t_token *token)
{
    if (!ft_strncmp(token->token, "echo", ft_strlen(token->token)))
        return 1;
    else if (!ft_strncmp(token->token, "cd", ft_strlen(token->token)))
        return 1;
    else if (!ft_strncmp(token->token, "pwd", ft_strlen(token->token)))
        return 1;
    else if (!ft_strncmp(token->token, "export", ft_strlen(token->token)))
        return 1;
    else if (!ft_strncmp(token->token, "unset", ft_strlen(token->token)))
        return 1;
    else if (!ft_strncmp(token->token, "env", ft_strlen(token->token)))
        return 1;
    else if (!ft_strncmp(token->token, "exit", ft_strlen(token->token)))
        return 1;
    return 0;
}
t_token *lexer(t_token *list)
{
    t_token *iterate;
    
    iterate = list;
    while (iterate != NULL)
    {
        if (check_if_builtin(iterate))
        {
            iterate->type = BUILTIN;
            if (iterate->next)
            {
                iterate = iterate->next;
                check_argument(iterate);
            }
        }
        else if (iterate->type == 0)
        {
            iterate->type = RANDOM;
        }
            iterate = iterate->next;
    }
    return list;
}
