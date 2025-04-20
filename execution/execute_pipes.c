# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

int count_pipe_line(t_execution *list)
{
    int count;
    count = 0;
    while(list && list ->args)
    {
        printf("%s",list->args[0]);
        if (list->outfile != -2 || list->infile != -2 || list->heredoc != -2 || list->append_flag != -2)
            return (count);
        printf("%d",count);
        count++;
        list = list->next;
    }
    return (count);
}

void exexute_pipes(char **path, t_execution *list, char **envp)
{
        // printf("%s",list->args[0]);
    int count = 1;
    int pipes[2][2];
    count = count_pipe_line(list);
    printf("%d",count);
}