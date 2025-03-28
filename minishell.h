/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:16:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/21 23:55:09 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "LIBFT/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

typedef struct s_global
{
    char *input;
    char **split;
    t_list *element;
} t_global;
void	ft_export_unset(t_global *input, char ***envp);
int	count_2D(char **envp);
void	ft_pwd();
void	ft_exit(t_global *input);
void	ft_chdir(t_global *input);
void	ft_env(char **envp);
void	ft_echo(t_global *input);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	is_builtin(char *cmd, char **envp, t_global *input);
void	ft_free_split(char **split);

#endif