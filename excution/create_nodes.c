#include "../includes/tokenizer.h"
#include "../includes/minishell.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strtok
#include <errno.h>  // For errno

int count_words(t_token *tokens)
{
    if (!tokens->token)
    return 0;
    int counter;
    counter = 0;
    while(tokens && tokens->type == WORD)
    {
        if (tokens->type == WORD)
            counter++;
        tokens = tokens->next;
    }
    return (counter);
}

t_new_list *ft_create_list(t_token *tokens)
{
    t_new_list *head = NULL;
    t_new_list *new_node = NULL;
    t_new_list *current = NULL;
    t_token *list = tokens;
    int i;
    int count;
    while (list)
    {
        if (list->type == WORD)
        {
            count = count_words(list);
            new_node = malloc(sizeof(t_new_list));
            if (!new_node)
                return (NULL);
            new_node->args = malloc(sizeof(char *) * (count + 1));
            if (!new_node->args)
            {
                free(new_node);
                return (NULL);
            }
            i = 0;
            while (i < count && list)
            {
                new_node->args[i] = ft_strndup(list->token, ft_strlen(list->token));
                if (!new_node->args[i])
                {
                    while (i >= 0)
                    {
                        free(new_node->args[i]);
                        i--;
                    }
                    free(new_node->args);
                    free(new_node);
                    return (NULL);
                }
                if (list->next)
                    flag_nodes(&new_node, list->next->type);
                else
                    new_node->type = ITS_CMD;
                list = list->next;
                i++;
            }
            new_node->args[i] = NULL;
            new_node->next = NULL;
            if (!head)
                head = new_node;
            else
                current->next = new_node;
            current = new_node;
            printf("Node args: %s\n", new_node->args[i]);
            printf("Node type: %d\n", new_node->type);
        }
        else
            list = list->next;
    }
    t_new_list *go = head;
    while(go)
    {
        printf("%s\n",go->args[0]);
        printf("%s\n",type_to_string2(go->type));
        go = go->next;
    }
    return (head);
}

void flag_nodes(t_new_list **node, t_type type)
{
    if(type == RED_IN)
        (*node)->type = ITS_RED_IN;
    else if (type == PIPE)
        (*node)->type = ITS_PIPE;
    else if (type == RED_OUT)
        (*node)->type = ITS_RED_OUT;
    else if (type == BUILTIN)
        (*node)->type = ITS_BUILTIN; 
    else if (type == APPEND)
        (*node)->type = ITS_APPEND;
    else if (type == HERE_DOC)
        (*node)->type = ITS_HERE_DOC;
    else
        (*node)->type = ITS_CMD;
}

char *resolve_command(char *command)
{
    char *path_env = getenv("PATH");
    char *path = NULL;
    char *full_path = NULL;

    if (!path_env)
        return NULL;

    path = strdup(path_env);
    if (!path)
        return NULL;

    char *dir = strtok(path, ":");
    while (dir)
    {
        full_path = malloc(strlen(dir) + strlen(command) + 2);
        if (!full_path)
        {
            free(path);
            return NULL;
        }
        sprintf(full_path, "%s/%s", dir, command);

        if (access(full_path, X_OK) == 0)
        {
            free(path); 
            return full_path;
        }

        free(full_path); 
        dir = strtok(NULL, ":");
    }

    free(path);
    return NULL;
}

void ft_execution(t_new_list *list)
{
    int pid;
    int status;
    char *command_path;
    if (!list || !list->args || !list->args[0])
    {
        write(2,"Error: No command to execute\n",30);
        return;
    }
    command_path = resolve_command(list->args[0]);
    if (!command_path)
    {
        write(2, "Error: Command not found: %s\n", 30);
        return;
    }
    pid = fork();
    if (pid == 0)
    {
        execve(command_path, list->args, NULL);
        perror("execve");
        free(command_path);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0) 
        waitpid(pid, &status, 0);
    free(command_path); 
}

// void ft_execution(t_new_list *list)
// {
//     int pid;
//     pid = fork();
//     if (pid == 0)
//     {
//         if (access(list->args[0],X_OK))
//             execve(list->args[0],list->args,NULL);
//         else
//             return ;
//     }
// }
