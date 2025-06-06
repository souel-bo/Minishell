/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 01:36:08 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/24 17:49:40 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	if (!ptr)
		return (0);
	while (*ptr)
		ptr++;
	return ((size_t)(ptr - s));
}
