/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souel-bo <souel-bo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 05:57:18 by souel-bo          #+#    #+#             */
/*   Updated: 2025/05/16 16:36:09 by souel-bo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
t_envp *g_new_envp;


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

void print(t_execution *list, t_token *list2)
{
    int i;
    
    while (list2)
    {
        if (list2->token[0] == '\0' && !list2->expanded)
            printf("a7a\n");
        else
            printf("{%s} %s [%d]\n", type_to_string(list2->type), list2->token, list2->index);
        list2 = list2->next;
    }
    if (list)
    {   
        while (list)
        {
                i = 0;
                while (list->args[i])
                {
                    printf("%s ", list->args[i]);
                    i++;
                }
                
                printf("\n[%d]\n", list->infile);
            if (list->file)
            {
                t_file *iterate = list->file;
    
                while (iterate)
                { 
                    printf("[%s] [%d] [%d] [%d] {%d}\n", iterate->file_name, iterate->infile, iterate->outfile, iterate->append, iterate->heredoc);
                    iterate = iterate->next;
                }
            }
            list = list->next;
        }
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
void ft_freeEnvp()
{
    t_envp *temp;
    while (g_new_envp)
    {
        temp = g_new_envp;
        g_new_envp = g_new_envp->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}
t_status *g_status()
{
    static t_status status = {0};
    return &status;
}

void handler(int sig)
{
    (void)sig;
    if (g_status()->flag == 0)
    {
        printf("\n");                
        rl_on_new_line();            
        rl_replace_line("", 0);      
        rl_redisplay();              
        g_status()->status = 130;    
    }
    else
        return;
}


void sig_child()
{
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*input;
	t_token	*tokens = NULL;
	t_execution	*pre = NULL;
    g_new_envp = NULL;
    g_new_envp = ft_create_envp(envp);
        signal(SIGINT, handler);
        signal(SIGQUIT, SIG_IGN);
	while (1)
	{
        g_status()->flag = 0;
        input = readline("minishell $>: ");
        if (!input)
        {
            ft_freeEnvp();
			exit(1);
        }
		add_history(input);
        g_status()->flag = 1;
		if (check_quotes(input))
		{
			ft_putstr_fd("minishell: syntax error: unclosed quotes\n", 2);
            g_status()->status = 2;
            free(input);
			continue;
		}
		tokens = tokenizer(input, tokens);
        if (parser(tokens))
        {
            ft_lstclear(&tokens, free);
            // free(input);
        }
		tokens = expantion(tokens);
		pre = pre_execution(tokens);
		print(pre, tokens);
        check_command_type(pre);
		ft_lstclear(&tokens, free);
		ft_lstclear_v2(&pre);
		free(input);
	}
    ft_freeEnvp();
}
