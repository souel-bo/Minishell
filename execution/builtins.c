#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/libft.h"

// 

int CountLenKey(char *line)
{
    int count = 0;
    while(*line != '=' && *line)
    {
        count++;
        line++;
    }
    return(count);
}
void	ft_chdir(t_execution *input)
{
	t_envp *tmp = new_envp;
	if (!input->args[1])
	{
		while(tmp)
		{
			if (ft_strncmp(tmp->key,"HOME",4))
			{
				chdir(getenv("HOME"));
				break;
			}
			tmp = tmp->next;
		}
	}
	else
	{
			chdir(input->args[1]);
			printf("%s %s\n","cd: no such file or directory:",input->args[1]);
	}
}

void	ft_echo(t_execution *input)
{
	int i;
	i = 1;
	int flag = 1;
	
	if (input->args[1])
	{
		if (strncmp(input->args[1], "-n", 2) == 0)
		{
			flag = 0;
			i++;
		}
	}
	while (input->args[i])
	{
		ft_putstr_fd(input->args[i], 1);
		if (flag == 1 && input->args[i + 1] == NULL)
			ft_putchar_fd('\n', 1);
		if (input->args[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

void	ft_env()
{
	t_envp *tmp = new_envp;
	while(tmp)
	{
		printf("%s=%s\n", tmp->key,tmp->value);
		tmp = tmp->next;
	}
}

t_envp	*AddToList(char *line)
{
	t_envp *node;
	int LenKey;
	LenKey = CountLenKey(line);
	node = malloc(sizeof(t_envp));
	if (!node)
		return NULL;
	node->key = ft_strndup(line,LenKey);
	if (line[LenKey] == '=' && line[LenKey + 1] != '\0')
	{
		node->value = ft_strndup(line + LenKey + 1, ft_strlen(line) - LenKey + 1);
	}
	else
		node->value = ft_strdup("");
	node->next = NULL;
	return(node);
}

void ft_export(t_execution *list)
{
	int i;
	i = 1;
	t_envp *node;
	while(list->args[i])
	{
		node = new_element2(list->args[i]);
		if (ft_strlen(node->value) > 0)
			ft_lstadd_back2(&new_envp,node);
		i++;
	}
}

int if_builtin(char *cmd)
{
    if (!ft_strncmp(cmd, "export", 6))
        return 1;

    if (!ft_strncmp(cmd, "unset", 5))
        return 1;

    if (!ft_strncmp(cmd, "pwd", 3))
        return 1;

    if (!ft_strncmp(cmd, "env", 3))
        return 1;

    if (!ft_strncmp(cmd, "exit", 4))
	{
        return 1;
	}
	if (!ft_strncmp(cmd,"cd",2))
		return 1;

	if (!ft_strncmp(cmd,"echo",4))
		return 1;
    return 0;
}

int	is_builtin(char *cmd, t_execution *list)
{
	if (!ft_strncmp(cmd, "export", 6))
		ft_export(list);
	if (!ft_strncmp(cmd, "unset", 5))
		ft_unset(list);
	if (!ft_strncmp(cmd, "pwd", 3))
		ft_pwd();
	if (!ft_strncmp(cmd, "env", 3))
		ft_env();	
	if (!ft_strncmp(cmd,"echo",4))
		ft_echo(list);
	if (!ft_strncmp(cmd,"cd",2))
		ft_chdir(list);
	return (0);
}
void ft_unset(t_execution *list)
{
    t_envp *prev = NULL;
    t_envp *current;
    int i = 1;

    while (list->args[i]) 
    {
        current = new_envp;
        prev = NULL;
        while (current) 
        {
            if (!ft_strncmp(list->args[i], current->key , ft_strlen(list->args[i])) &&
                current->key[ft_strlen(list->args[i])] == '\0') 
            {
                if (prev == NULL) 
                    new_envp = current->next;
                else 
                    prev->next = current->next;
                free(current->key);
                free(current->value);
                free(current);
                break;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
}

void	ft_exit(t_execution *input)
{
	int status;
	status = 0;
	if (input->args[1])
	{
		status = ft_atoi(input->args[1]);
	}
	exit(status);
}

void	ft_pwd()
{
	char *buf;
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(1);
	}
	printf("%s\n", buf);
	free(buf);
}

char	**listToArray()
{
	int size;
	char *tmp;
	char *tmp2;
	int i = 0;
	char **envpExecve;
	size = ft_lstsize_envp(new_envp);
	envpExecve = malloc(sizeof(char *) * (size + 1));
	t_envp *head = new_envp;
	while(head)
	{
		tmp2 = ft_strjoin(head->key,"=");
		tmp = ft_strjoin(tmp2,head->value);
		envpExecve[i] = ft_strndup(tmp,ft_strlen(tmp));
		i++;
		free(tmp);
		free(tmp2);
		head = head->next;
	}
	envpExecve[i] = NULL;
	return(envpExecve);
}

t_envp *ft_create_envp(char **envp)
{
    int i = 0;
    t_envp *head = NULL;
    t_envp *node;
    if (!envp)
        return (NULL);
   while (envp[i])
	{
		node = new_element2(envp[i]);
		if (!node)
		{
			while (head)
			{
				t_envp *tmp = head->next;
				free(head);
				head = tmp;
			}
			return (NULL);
		}
		ft_lstadd_back2(&head, node);
		i++;
	}
    return (head);
}

t_envp	*new_element2(char *line)
{
	t_envp *new;
    if (!line)
        return NULL;
    char *key = NULL;
    char *value = NULL;
	int lenKey  = CountLenKey(line);
	key = ft_strndup(line,lenKey);
	value = ft_strndup(line + lenKey + 1,ft_strlen(line) - lenKey);
	new = malloc(sizeof(t_envp));
	if (!new)
		return (NULL);
	new->key = key;
    new->value = value;
	new->next = NULL;
	return (new);
}

t_envp	*ft_lstlast2(t_envp *lst)
{
	t_envp	*last_content;

	if (!lst)
		return (NULL);
	last_content = lst;
	while (last_content != NULL && last_content->next != NULL)
	{
		last_content = last_content->next;
	}
	return (last_content);
}

void	ft_lstadd_back2(t_envp **lst, t_envp *new)
{
	t_envp	*last;
	if (!new || !lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast2(*lst);
		last->next = new;
	}
}
