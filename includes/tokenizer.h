/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfyn <sfyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:56:13 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/05 12:50:45 by sfyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "minishell.h"

t_token *tokenizer(char *input, t_token *tokens);
int check_quotes(char *input);
int check_parenthis(char *input);
#endif