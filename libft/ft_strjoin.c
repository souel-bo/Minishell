/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/29 00:07:57 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/29 00:12:17 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*aloc_str;
	size_t	len;

	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	if (!s1 && !s2)
		return (NULL);
	len = (ft_strlen(s1) + ft_strlen(s2)) + 1;
	aloc_str = (char *)malloc
		(sizeof(char) * (len));
	if (!aloc_str)
		return (NULL);
	ft_strlcpy(aloc_str, s1, ft_strlen(s1) + 1);
	ft_strlcat(aloc_str, s2, 1);
	return (aloc_str);
}