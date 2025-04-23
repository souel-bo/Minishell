#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/tokenizer.h"


void	execute_simple_cmnd(char **path, t_execution *list, char **envp)
{
	char	*temp;
	char	*full_cmd;
	int (i) = 0;
  
	while (path[i])
	{
		if (access(list->args[0], X_OK) == 0)
		return (execve(list->args[0], list->args, envp),
			ft_free(list->args), exit(1));
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (ft_free(path), ft_free(list->args));
		full_cmd = ft_strjoin(temp, list->args[0]);
		free(temp);
		if (!full_cmd)
			return (ft_free(path), ft_free(list->args));
		if (access(full_cmd, X_OK) == 0)
		{
			ft_free(path);
			if (list->infile != -2)
			{
				printf("lekhra\n");
				if (list->infile == -1)
					printf("%s : %s",list->args[0],"no file");
				else
					dup2(list->infile, 0);
			}
			if (list->outfile != -2)
				dup2(list->outfile, 1);
			if (execve(full_cmd, list->args, envp))
				write(2, "execve failed\n", 14);
			return (free(full_cmd), ft_free(list->args));
		}
		free(full_cmd);
		i++;
	}
	write(2, list->args[0], ft_strlen(list->args[0]));
	write(2, " : command not found\n", 22);
	return (ft_free(path), ft_free(list->args),exit(127));
}

void	helper_pipeline(char **path, char **cmd, char **envp)
{
	char	*temp;
	char	*full_cmd;
	int (i) = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		if (!temp)
			return (ft_free(path), ft_free(cmd));
		full_cmd = ft_strjoin(temp, cmd[0]);
		free(temp);
		if (!full_cmd)
			return (ft_free(path), ft_free(cmd));
		if (access(full_cmd, X_OK) == 0)
		{
			ft_free(path);
			if (execve(full_cmd, cmd, envp))
				write(2, "execve failed\n", 14);
			return (free(full_cmd), ft_free(cmd));
		}
		free(full_cmd);
		i++;
	}
	write(2, cmd[0], ft_strlen(cmd[0]));
	write(2, " : command not found\n", 22);
	return (ft_free(path), ft_free(cmd));
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
