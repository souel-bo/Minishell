# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

// int count_pipe_line(t_execution *list)
// {
//     int count;
//     count = 0;
//     while(list && list ->args)
//     {
//         if (list->outfile != -2 || list->infile != -2 || list->heredoc != -2 || list->append_flag != -2)
//             return (count);
//         count++;
//         list = list->next;
//     }
//     return (count);
// }

void execute_pipes(char **path, t_execution *list, char **envp)
{
    int i = 0;
    int size = ft_lstsize(list);
    int pipes[2][2];
    pid_t pid;
    // count = count_pipe_line(list);
    // printf("%d",count);
    while(i < size)
    {
        if (i < size - 1)
            pipe(pipes[i % 2]);
        pid = fork();
        if (pid == 0)
        {
            if (i > 0 )
                dup2(pipes[(i + 1) % 2][0],0);
            if (i < size - 1)
                dup2(pipes[i % 2][1],1);
            if (i < size - 1)
            {
                close(pipes[i % 2][0]);
                close(pipes[i % 2][1]);
            }
            execute_simple_cmnd(path,list->args,envp);
        }
        if (i < 0) 
        {
            close(pipes[(i + 1) % 2][0]);
            close(pipes[(i + 1) % 2][1]);
        }
        if (i < size - 1)
        {
            close(pipes[i % 2][1]);
            // close(pipes[i % 2][0]);
        }
        i++;
        list = list->next;
    }
    while (wait(NULL) > 0);
}