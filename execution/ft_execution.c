# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

void ft_execution(t_execution *list,char **envp)
{
    int pid;
    char **path;
    pid = fork();
    if (pid == 0)
    {
        path = get_path();
        if (!path)
            return (ft_free(path), ft_free(list->args));
        if (ft_lstsize(list) == 1)
            execute_simple_cmnd(path,list->args,envp);
        else if (ft_lstsize(list) > 1)
			execute_pipes(path,list,envp);
    }
    waitpid(pid, 0, 0);
}