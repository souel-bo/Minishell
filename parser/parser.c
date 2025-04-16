/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 11:49:01 by sfyn              #+#    #+#             */
/*   Updated: 2025/04/16 21:54:03 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenizer.h"

int check_quotes(char *input)
{
    int i = 0;
    int single_quotes = 0;
    int double_quotes = 0;
    while (input[i])
    {
        if (input[i] == '\"')
        {
            double_quotes++;
            i++;
            while (input[i] && input[i] != '\"')
                i++;
            if (input[i] == '\"')
                double_quotes++;
        }
        else if (input[i] == '\'')
        {
            single_quotes++;
            i++;
            while (input[i] && input[i] != '\'')
                i++;
            if (input[i] == '\'')
                single_quotes++;
        }
        i++;
    }
    if (double_quotes % 2 != 0 || single_quotes % 2 != 0)
        return 1;
    return 0;
}

int parser(char *input)
{
    if (input[0] == '|' && input[1] != '|')
    {
        ft_putstr_fd("minishell: parse error near '|'\n", 2);
        return 1;
    }
    printf("test\n");
    return 0;
}


int check_parenthis(char *input)
{
    int i = 0;
    int open_parenthis = 0;
    while (input[i])
    {
        if (input[i] == ')' && open_parenthis == 0)
        {
            ft_putstr_fd("minishell: parse error near `)'\n", 2);
            return 1;
        }
        else if (input[i] == '(' && open_parenthis == 0)
        {
            i++;
            open_parenthis = 1;
            while (input[i] && input[i] != ')')
            {
                if (input[i] == '(')
                {
                    ft_putstr_fd("minishell: parse error near `('\n", 2);
                    return 1;
                }
                i++;
            }
            if (input[i] == ')' && input[i - 1] == '(')
            {
                ft_putstr_fd("minishell : (empty subshell)\n", 2);
                return 1;
            }
            else if (input[i] == ')')
                open_parenthis = 0;
        }
        i++;
    }
    if (input[i] == '\0' && open_parenthis == 1)
    {
        ft_putstr_fd("minishell : unclosed subshell `('\n", 2);
        return 1;
    }
    return 0;
}

int count_words(t_token *tokens)
{
	t_token *iterator;
	iterator = tokens;
	int i = 0;
	while (iterator)
	{
		if (iterator->type == PIPE)
			break;
		i++;
		iterator = iterator->next;
	}	
	return i;
}

t_execution *create_element(t_token *tokens)
{
	t_execution *element;
	element = malloc(sizeof(t_execution));
	if (!element)
		return NULL;
	element->args = malloc(sizeof(char *) * (count_words(tokens) + 1));
	if (!element->args)
		return NULL;
    element->heredoc = -1;
    element->infile = -1;
    element->outfile = -1;
    element->append_flag = -1;
    element->next = NULL;
	return element;
}

t_token *copy_elements(t_execution *exec, t_token *iterate)
{
    int i = 0;
    while (iterate)
    {
        if (iterate->type == PIPE)
            break;
        exec->args[i] = ft_strndup(iterate->token, ft_strlen(iterate->token));
        i++;
        iterate = iterate->next;
    }
    exec->args[i] = NULL;
    return iterate;
}

t_execution	*ft_lstlast_v2(t_execution *lst)
{
	t_execution	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

void	ft_lstadd_back_v2(t_execution **lst, t_execution *new)
{
	t_execution	*last;

	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast_v2(*lst);
		last->next = new;
	}
}

// int open_file(t_token *token)
// {
//     if (token->type == RED_IN)
//     {
//         token = token->next;
        
//     }
// 	return (0);
// }

t_execution *pre_execution(t_token *tokens)
{
    t_execution *exec_list = NULL;
    t_execution *temp = NULL;
    t_token *iterate = tokens;

    while (iterate)
    {
        if (iterate->type == PIPE)
            iterate = iterate->next;
        // else if (iterate->type == RED_IN 
        // || iterate->type == RED_OUT 
        // || iterate->type == APPEND)
        // {
        //     if (!open_file(iterate))
		// 		return NULL;
        // }
        temp = create_element(iterate);
        iterate = copy_elements(temp, iterate);
        ft_lstadd_back_v2(&exec_list, temp);
    }
    return exec_list;
}
