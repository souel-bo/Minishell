/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtinsUtils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:24:58 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/05/24 15:09:50 by yaaitmou         ###   ########.fr       */
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
	if (number[i] == '\0')
		return (1);
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
		ft_freenvp();
		free_and_exit();
	}
}

int	array_len(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (-1);
	while (args[i])
		i++;
	return (i);
}

void	check_number(t_execution *input, int size)
{
	int (j) = 0;
	int (check) = 0;
	if (input->args[1][j] == '\0')
		num_error(input, size);
	check = ft_atoi(input->args[1], &j);
	if (j == 1)
		num_error(input, size);
	else
		g_status()->status = check;
	if (size == 1)
	{
		ft_freenvp();
		free_and_exit();
	}
}

void	redir_free(t_execution *list)
{
	ft_redirection(list->file);
	ft_freenvp();
	ft_lstclear_v2(&g_status()->original_list);
}
