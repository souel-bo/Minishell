# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

void ft_execution(t_execution *list)
{
    int size;  
    char **path; 
    path = get_path();
    size = ft_lstsize(list);
    execute_pipes(path,list,size);
}