# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

void ft_execution(t_execution *list,int *status)
{
    int size;
    size = count_pipe_line(list);
    execute_pipes(list,size,status);
}