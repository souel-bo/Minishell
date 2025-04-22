# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

int count_pipe_line(t_execution *list)
{
    int count;
    count = 0;
    while(list && list ->args)
    {
        count++;
        if (list->outfile != -2 || list->infile != -2)
            return (count);
        list = list->next;
    }
    return (count);
}

void execute_pipes(char **path, t_execution *list, char **envp,int size)
{
    int i = 0;
    int pipes[2][2];
    pid_t *pid = malloc(sizeof(pid_t) * size);
    while(i < size)
    {
        if (i < size - 1)
            pipe(pipes[i % 2]);
        pid[i] = fork();
        if (pid[i] == 0)
        {
            if (i > 0)
                dup2(pipes[(i + 1) % 2][0], 0);
            if (i < size - 1)
                dup2(pipes[i % 2][1], 1);
            if (list->infile != -2)
                dup2(list->infile, STDIN_FILENO);
            if (list->outfile != -2)
                dup2(list->outfile, STDOUT_FILENO);
            close(pipes[i % 2][0]);
            close(pipes[i % 2][1]);
            helper_pipeline(path,list->args,envp);
        }
        if (i > 0) 
            close(pipes[(i + 1) % 2][0]);
        if (i < size - 1)
            close(pipes[i % 2][1]);
        i++;
        list = list->next;
    }
    i = 0;
    while(i < size)
    {
        waitpid(pid[i], NULL, 0);
        i++;
    }
}
