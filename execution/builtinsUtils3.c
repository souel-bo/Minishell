/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsUtils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:24:58 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/22 21:08:17 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	checkifnum(char *number)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if ((number[j] == '-') || (number[j] == '+'))
		j++;
	while (number[i])
	{
		if (number[j] >= 48 && number[j] <= 57)
			j++;
		i++;
	}
	if (j == i)
		return (1);
	return (0);
}

void	num_error(t_execution *input, int size)
{
	print_error2("bash: exit: ",
		input->args[1], ": numeric argument required", 2);
	if (size == 1)
	{
		ft_freeEnvp();
		free_and_exit();
	}
}

int	array_len(char **args)
{
	int i;
	i = 0;
	if (!args)
		return -1;
	while(args[i])
		i++;
	return (i);
}