/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sfyn <sfyn@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 01:41:04 by souel-bo          #+#    #+#             */
/*   Updated: 2025/04/02 11:57:33 by sfyn             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
#define LIBFT_H

#include "minishell.h"

t_token	*new_element(char *ptr);
size_t	ft_strlen(const char *s);
char *ft_strndup(char *s, size_t n);
char	*ft_strchr(const char *s, int c);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstclear(t_token **lst, void (*del)(void *));
void	ft_lstdelone(t_token *lst, void (*del)(void*));
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
#endif