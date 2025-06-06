/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 01:41:04 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 20:38:17 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include "minishell.h"

char	*ft_strdup(char *s);
int		ft_atoi(char *str, int *j);
t_token	*new_element(char *ptr);
size_t	ft_strlen(const char *s);
char	*ft_strndup(char *s, size_t n);
char	*ft_strchr(const char *s, int c);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstclear(t_token **lst, void (*del)(void *));
void	ft_lstdelone(t_token *lst, void (*del)(void *));
char	*ft_strjoin(char *s1, char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_is_alpha(int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isdigit(int c);
int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
char	*ft_itoa(int n);
char	*ft_strjoin_heredoc(char *s1, char *s2);
int		ft_strcmp(const char *s1, const char *s2);
#endif
