/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/06 12:34:13 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
t_envp *new_envp;


const char *type_to_string(t_type type)
{
    if (type == BUILTIN)
        return "BUILTIN";
    else if (type == PIPE)
        return "PIPE";
    else if (type == RED_IN)
        return "RED_IN";
    else if (type == RED_OUT)
        return "RED_OUT";
    else if (type == FILE_NAME)
        return "FILE_NAME";
	else if (type == HERE_DOC)
        return "HERE_DOC";
	else if (type == DELIMITER)
        return "DELIMITER";
	else if (type == APPEND)
        return "APPEND";
	else if (type == ARGUMENT)
        return "ARGUMENT";
    return "WORD";
}

void print(t_execution *list, t_token *list2, t_envp *env)
{
    int i;
    (void)env;
    while (list2)
    {
        printf("{%s} %s\n", type_to_string(list2->type), list2->token);
        list2 = list2->next;
    }
    // if (env)
    // {
    //     while (env)
    //     {
    //         printf("%s %s\n", env->key,env->value);
    //         env = env->next;
    //     }
    // }
    while (list)
    {
            i = 0;
            while (list->args[i])
            {
                printf("%s ", list->args[i]);
                i++;
            }   
            printf("\n");
        if (list->file)
        {
            t_file *iterate = list->file;

            while (iterate)
            { 
                printf("[%s] [%d] [%d] [%d]\n", iterate->file_name, iterate->infile, iterate->outfile, iterate->append);
                iterate = iterate->next;
            }
        }
        list = list->next;
    }
}

int check_space(char *input)
{
    int i = 0;
    while (input[i] && (input[i] == ' ' || input[i] == '\t'))
          i++;
    if (input[i] == '\0')
        return 1;
    return 0;
}
void ft_freeEnvp(t_envp *envp)
{
    t_envp *temp;
    while (envp)
    {
        temp = envp;
        envp = envp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
    (void)envp;
	char	*input;
	t_token	*tokens = NULL;
	t_execution	*pre = NULL;
	int	status = 0;
    new_envp = NULL;
    new_envp = ft_create_envp(envp);
	while (1)
	{
		input = readline("minishell $>: ");
		if (!input)
			exit(1);
		if (check_space(input))
		{
			free(input);
			continue;
		}
		add_history(input);
		if (check_quotes(input, &status))
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
		    printf("%d\n", status);
            free(input);
			continue;
		}
		tokens = tokenizer(input, tokens);
		tokens = expantion(tokens, new_envp);
		pre = pre_execution(tokens);
		// print(pre, tokens, new_envp);
		// printf("%d\n", status);
		// ft_execution(pre,&status);
		ft_lstclear(&tokens, free);
		ft_lstclear_v2(&pre);
		free(input);
	}
}

