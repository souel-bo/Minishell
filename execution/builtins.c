#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/libft.h"

void	ft_env()
{
	t_envp *tmp = new_envp;
	while (tmp)
	{
		if (tmp->key && tmp->value != NULL)
			printf("%s=%s\n", tmp->key,tmp->value);
		tmp = tmp->next;
	}
}

void ft_export(t_execution *list)
{
	int i;
	i = 1;
	t_envp *node;
	t_envp *export = new_envp;
	while(list->args[i])
	{
		if (check_sen(list->args[i]) == 0)
		{
			printf("bash: export: `%s': not a valid identifier\n",list->args[i]);
			i++;
		}
		else if (already_in(list->args[i]) == 1)
			i++;
		else
		{
			node = new_element2(list->args[i]);
			ft_lstadd_back2(&new_envp,node);	
			i++;
		}
	}
	if (!list->args[1])
	{
		while(export)
		{
			if (export->key && export->value)
				printf("declare -x %s=\"%s\"\n", export->key, export->value);
			else if (export->key)
				printf("declare -x %s\n", export->key);
			export = export->next;
		}
	}
}

void ft_unset(t_execution *list)
{
    t_envp *prev = NULL;
    t_envp *current;
    int (i) = 1;
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

void	ft_exit(t_execution *input,int size)
{
	int status;
	status = 0;
	if (size == 1)
		printf("%s\n","exit");
	if (checkIfNum(input->args[1]))
	{
		printf("bash: exit: %s: numeric argument required\n",input->args[1]);
		exit(2);
	}
	else if (input->args[2])
	{
		printf("bash: exit: too many arguments\n");
		g_status()->status = 1;
	}
	else if (input->args[1])
	{
		status = ft_atoi(input->args[1]);
		exit (status);
	}
	exit(g_status()->status >> 8);
}

void	ft_pwd()
{
	char *buf;
	buf = getcwd(NULL, 0);
	if (!buf)
		printf("%s\n",searchAndsave("PWD"));
	else
		printf("%s\n", buf);
	free(buf);
	g_status()->status = 0;
}
