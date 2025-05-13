#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/libft.h"

int	already_in(char *arg)
{
	t_envp	*tmp = new_envp;
	char	*key;
	char	*new_value;
	int		lenKey;
	int		append = 0;
	lenKey = CountLenKey(arg);
	if (arg[lenKey] == '+' && arg[lenKey + 1] == '=')
		append = 1;
	key = ft_strndup(arg, lenKey);
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, lenKey) == 0 && tmp->key[lenKey] == '\0')
		{
			if (append)
				new_value = ft_strjoin(tmp->value, arg + lenKey + 2); 
			else
				new_value = ft_strdup(arg + lenKey + 1); 

			free(tmp->value);
			tmp->value = new_value;
			free(key);
			return (1);
		}
		tmp = tmp->next;
	}
	free(key);
	return (0);
}
int if_builtin(char *cmd)
{
    if (!ft_strcmp(cmd, "export") )
        return 1;
    else if (!ft_strcmp(cmd, "unset"))
        return 1;
    else if (!ft_strcmp(cmd, "pwd"))
        return 1;
    else if (!ft_strcmp(cmd, "env"))
        return 1;
    else if (!ft_strcmp(cmd, "exit"))
        return 1;

	else if (!ft_strcmp(cmd,"cd"))
		return 1;

	else if (!ft_strcmp(cmd,"echo"))
		return 1;
	else if(!ft_strcmp(cmd,"exit"))
		return 1;
    return 0;
}
