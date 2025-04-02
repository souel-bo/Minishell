/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfyn <sfyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/04/02 12:02:43 by sfyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int check_quotes(char *input)
{
    int i = 0;
    int quotes = 0;
    while (input[i])
    {
        if (input[i] == '\"')
            quotes++;
        i++;
    }
    if (quotes % 2 != 0)
        return 1;
    return 0;
}
