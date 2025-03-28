/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 01:29:33 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/28 04:20:03 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(char *s, size_t n)
{
	size_t i = 0;
	char *str;
	if (!s)
		return (NULL);
	str = malloc(n + 1);
	if (!str)
		return (NULL);
	while (i < n && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
