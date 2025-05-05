# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

void ft_execution(t_execution *list,int *status)
{
    int size;  
    char **path; 
    path = get_path();
    size = count_pipe_line(list);
    execute_pipes(path,list,size,status);
}