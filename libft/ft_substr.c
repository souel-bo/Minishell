/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:37:17 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 17:51:10 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;

	if (!s)
		return (NULL);
	if ((size_t)start >= ft_strlen(s))
	{
		sub_str = ft_strdup("");
		return (sub_str);
	}
	if (len > ft_strlen(s) - (size_t)start)
		len = ft_strlen(s) - (size_t)start;
	sub_str = (char *)malloc
		((sizeof(char)) * (len + 1));
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + (size_t)start, len + 1);
	sub_str[len] = '\0';
	return (sub_str);
}
