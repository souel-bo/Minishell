#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/tokenizer.h"

char *searchAndsave(char *var)
{
	t_envp *tmp = new_envp;
	while(tmp)
	{
		if(strncmp(var,tmp->key,ft_strlen(var)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return NULL;
}

int	search_in_env(char *var)
{
	t_envp *tmp = new_envp;
	while(tmp)
	{
		if(strncmp(var,tmp->key,ft_strlen(var)) == 0)
			return (1);
		tmp = tmp->next;
	}
	return 0;
}
int	change_in_env(char *var,char *buf)
{
	t_envp *tmp = new_envp;
	while(tmp)
	{
		if(strncmp(var,tmp->key,ft_strlen(var)) == 0)
		{
			free(tmp->value);
			tmp->value = buf;
			return 1;
		}
		tmp = tmp->next;
	}
	return 0;
}
int CountLenKey(char *line)
{
	int count = 0;
	while (line[count] && line[count] != '=' && !(line[count] == '+' && line[count + 1] == '='))
		count++;
	return (count);
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
