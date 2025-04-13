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
int ft_isprint(int c)
{
    return (c >= 32 && c <= 126);
}
char	**get_path()
{
    char *PATH;
    PATH = getenv("PATH");
	return (ft_split(PATH, ':'));
}

void	execve_path(char **path, char **cmd, char **envp)
{
	char	*temp;
	char	*full_cmd;

	int (i) = 0;
    
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (ft_free(path), ft_free(cmd), exit(1));
		full_cmd = ft_strjoin(temp, cmd[0]);
        printf("full_cmd: %s\n %s\n", full_cmd,cmd[0]);
		free(temp);
		if (!full_cmd)
			return (ft_free(path), ft_free(cmd), exit(1));
		if (access(full_cmd, X_OK) == 0)
		{
			ft_free(path);
			if (execve(full_cmd, cmd, envp))
				write(2, "execve failed\n", 14);
            return (free(full_cmd), ft_free(cmd), exit(1));
		}
		free(full_cmd);
		i++;
	}
	write(2, "command not found\n", 18);
	return (ft_free(path), ft_free(cmd), exit(127));
}
void ft_execution(t_new_list *list,char **envp)
{
    int pid;
    char **path;
    pid = fork();
    if (pid == 0)
    {
        path = get_path();
        execve_path(path,list->args,envp);
    }
}
