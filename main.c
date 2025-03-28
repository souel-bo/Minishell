/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 20:24:27 by souel-bo          #+#    #+#             */
/*   Updated: 2025/03/21 23:06:50 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "LIBFT/libft.h"
void print_element(t_list *list)
{
    int i = 1;
    while (list != NULL)
    {
        printf("argument num : %d is : %s\n", i, (char *)list->content);
        i++;
        list = list->next;   
    }
    ft_lstclear(&list, free);
}

t_list *lexer(t_global *input, t_list *list)
{
    int i = 0;
    input->split = ft_split(input->input, ' ');
    if (!input->split)
    {
        ft_putstr_fd("lexer failed\n", 2);
        exit(1);
    }
    while (input->split[i])
    {
        input->element = ft_lstnew(ft_strdup(input->split[i]));        ;
        ft_lstadd_back(&list, input->element);
        i++;
    }
    // ft_free_split(input->split);
    // input->split = NULL;
    return list;
}

char **make_envp(char **envp,char **new_envp)
{
    int i = 0;
    while (envp[i])
    {
        new_envp[i] = ft_strdup(envp[i]);
        i++;
    }
    new_envp[i] = NULL;
    return new_envp;
}

void open_promt(t_global *promt, t_list *list, char **envp)
{
    char **new_envp = malloc(sizeof(char *) * (count_2D(envp) + 1));
    if (!new_envp)
        exit(1);
    new_envp = make_envp(envp, new_envp);
    promt = malloc(sizeof(t_global));
    if (!promt)
        exit(0);
    while (1)
    {
        promt->input = readline("Minishell $>: ");
        promt->element = NULL;
        if (list)
        {
            ft_lstclear(&list, free);
            list = NULL;
        }
        list = lexer(promt, list);
        print_element(list);
        if (is_builtin(list->content, new_envp, promt))
            return ;
        free(promt->input);
        if (!promt->input)
        {
            if (promt->split)
                ft_free_split(promt->split);
            if (promt->element)
                free(promt->element);
            if (promt)
                free(promt);
            exit(0);
        }
    }
}

int main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    t_global *promt = NULL;
    t_list *list = NULL;
    open_promt(promt, list, env);
    return 0;
}