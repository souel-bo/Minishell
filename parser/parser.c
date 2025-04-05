/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfyn <sfyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/04/05 13:40:46 by sfyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int check_quotes(char *input)
{
    int i = 0;
    int single_quotes = 0;
    int double_quotes = 0;
    while (input[i])
    {
        if (input[i] == '\"')
        {
            double_quotes++;
            i++;
            while (input[i] && input[i] != '\"')
                i++;
            if (input[i] == '\"')
                double_quotes++;
        }
        else if (input[i] == '\'')
        {
            single_quotes++;
            i++;
            while (input[i] && input[i] != '\'')
                i++;
            if (input[i] == '\'')
                single_quotes++;
        }
        i++;
    }
    if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
        return 1;
    return 0;
}
int check_parenthis(char *input)
{
    int i = 0;
    int open_parenthis = 0;
    while (input[i])
    {
        if (input[i] == ')' && open_parenthis == 0)
        {
            ft_putstr_fd("minishell: parse error near `)'\n", 2);
            return 1;
        }
        else if (input[i] == '(' && open_parenthis == 0)
        {
            i++;
            open_parenthis = 1;
            while (input[i] && input[i] != ')')
            {
                if (input[i] == '(')
                {
                    ft_putstr_fd("minishell: parse error near `('\n", 2);
                    return 1;
                }
                i++;
            }
            if (input[i] == ')' && input[i - 1] == '(')
            {
                ft_putstr_fd("minishell : (empty subshell)\n", 2);
                return 1;
            }
            else if (input[i] == ')')
                open_parenthis = 0;
        }
        i++;
    }
    if (input[i] == '\0' && open_parenthis == 1)
    {
        ft_putstr_fd("minishell : unclosed subshell `('\n", 2);
        return 1;
    }
    return 0;
}
