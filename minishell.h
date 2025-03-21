/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:16:37 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/20 15:51:55 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

# include "LIBFT/libft.h"
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_global
{
    char *input;
    char **split;
    t_list *element;
} t_global;

void	ft_free_split(char **split);

#endif