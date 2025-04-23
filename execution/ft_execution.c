# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

void ft_execution(t_execution *list,char **envp)
{
    char **path;
    int size;
    path = get_path();
    size = count_pipe_line(list);
    if (!path)
            return (ft_free(path), ft_free(list->args));
    execute_pipes(path,list,envp,size);
    ft_free(path);
}