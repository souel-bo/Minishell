/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 17:39:54 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 17:41:53 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

#include <limits.h>

static int	check_overflow(unsigned long long result,
				int digit, int sign)
{
	unsigned long long	limit;

	if (sign == 1)
		limit = LLONG_MAX;
	else
		limit = (unsigned long long)LLONG_MAX + 1;
	if (result > limit / 10
		|| (result == limit / 10 && (unsigned long long)digit > limit % 10))
		return (1);
	return (0);
}

static int	parse_number(char *str, int *i, int sign, long long *final)
{
	unsigned long long	result;
	int					digit;

	result = 0;
	if (str[*i] < '0' || str[*i] > '9')
		return (999);
	while (str[*i] >= '0' && str[*i] <= '9')
	{
		digit = str[*i] - '0';
		if (check_overflow(result, digit, sign))
			return (999);
		result = result * 10 + digit;
		(*i)++;
	}
	if (str[*i] != '\0')
		return (999);
	if (sign == 1)
		*final = (long long)result;
	else
		*final = -(long long)result;
	return (0);
}

int	ft_atoi(char *str, int *j)
{
	long long (final);
	int (i) = 0;
	int (sign) = 1;
	if (!str || str[0] == '\0')
		return (999);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (parse_number(str, &i, sign, &final) != 0)
	{
		(*j) = 1;
		return (0);
	}
	return ((unsigned char)final);
}
