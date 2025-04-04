/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfyn <sfyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/04/04 11:41:45 by sfyn             ###   ########.fr       */
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
