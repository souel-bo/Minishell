#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/libft.h"

void check_builtin(t_execution *list, int size)
{
    int stdout_copy = dup(1);
    int stdin_copy = dup(0);
    if (list->file)
    {
        if (ft_redirection(list->file) == 0)
        {
            is_builtin(list->args[0], list,size);
            dup2(stdout_copy,1);
            dup2(stdin_copy,0);
        }
    }
    else
    {
        is_builtin(list->args[0], list,size);
        dup2(stdout_copy,1);
        dup2(stdin_copy,0);
    }
    close (stdout_copy);
    close (stdin_copy);
}
int	check_sen(char *list)
{
	int j = 0;
	if ((list[0] != '_') && (!ft_isalpha(list[0])))
		return 0;
	while(list[j] && list[j] != '=')
	{
		if (list[j] == '+' && list[j + 1] == '=')
		{
			j++;
		}
		if ((ft_isalnum(list[j]) == 0) && list[j] != '=')
			return 0;
		j++;
	}
	return 1;
}
int checkIfNum(char *number)
{
	int j = 0;
	int i = 0;
	if (!number)
		exit(g_status()->status >> 8);
	while(number[i])
	{
		if (number[j] >= 48 && number[j] >= 57)
			j++;
		i++;
	}
	if (j == i)
		return 1;
	else
		return 0;
}

t_envp *new_element2(char *line)
{
    char *key;
	t_envp *new;
    if (!line)
        return NULL;
    int lenKey = CountLenKey(line);
	key = ft_strndup(line, lenKey);
    char *value = NULL;
    if (line[lenKey] == '=')
    {
        if (line[lenKey + 1] != '\0')
            value = ft_strdup(line + lenKey + 1);
        else
            value = ft_strdup("");
	}
	if (line[lenKey] == '+')
	{
		if (line[lenKey + 2] != '\0')
            value = ft_strdup(line + lenKey + 2);
        else
            value = ft_strdup("");	
	}
    new = malloc(sizeof(t_envp));
    if (!new)
    {
        free(key);
        free(value);
        return NULL;
    }
    new->key = key;
    new->value = value;
    new->next = NULL;
    return new;
}
void	is_builtin(char *cmd,t_execution *list,int size)
{
	if (!ft_strcmp(cmd, "export"))
		ft_export(list);
	if (!ft_strcmp(cmd, "unset"))
		ft_unset(list);
	if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	if (!ft_strcmp(cmd, "env"))
		ft_env();
	if (!ft_strcmp(cmd,"echo"))
		ft_echo(list);
	if (!ft_strcmp(cmd,"cd"))
		ft_chdir(list);
	if (!ft_strcmp(cmd, "exit"))
		ft_exit(list,size);
}
