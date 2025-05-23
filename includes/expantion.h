/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:00:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/23 13:18:38 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANTION_H
# define EXPANTION_H

# include "minishell.h"

t_token	*expantion(t_token *tokens);
t_token	*expand_value(t_token *token);
void	join_value(char *temp, const char *s, int *j);
char	*expand_env(char *key);
int	is_special(char c);
int	find_dollar(char *s);
int	check_quote(char *delimiter);
void	set_quote(t_token *new);
#endif