/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expantion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 19:00:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 18:02:41 by souel-bo         ###   ########.fr       */
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
void	expand_exit_status(t_norm_v2 *obj);
void	expand_single_quote(t_norm_v2 *obj, t_token *iterate);
int	check(t_norm_v2 *obj, t_token *iterate);
int	check_2(t_norm_v2 *obj, t_token *iterate);
void	copy_variable(t_norm_v2 *obj, t_token *iterate);
void	normal_expand(t_norm_v2 *obj, t_token *iterate);
void	finish_it(t_norm_v2 *obj);
void	skip(t_norm_v2 *obj, t_token *iterate);
void	helper(t_norm_v2 *obj, t_token *iterate);
void	expand_double_quote(t_norm_v2 *obj, t_token *iterate);
t_token	*handle_quote(t_token *tokens);
void	single_quote(t_token *iterate, int *i, int *j, char *temp);
void	set_and_clean(t_token **iterate, int *j, char *temp);
void	double_quote(t_token *iterate, int *i, int *j, char *temp);
#endif