# include "../includes/minishell.h"
# include "../includes/libft.h"
# include "../includes/tokenizer.h"

int is_dir(char *path)
{
    struct stat buf;
    if (stat(path,&buf) == 0)
        return (S_ISDIR(buf.st_mode));
    return 0;
}

void print_error(char *name,char *error)
{
    ft_putstr_fd(name, 2);
    ft_putstr_fd(error ,2);
    ft_putchar_fd('\n',2);
}

int execute_cmd(t_execution *list,char *cmd)
{
    int pid;
    pid = fork();
    if (pid == 0)
    {
        if (ft_redirection(list->file) == 1)
            exit(1);
        else
            execve(cmd,list->args,listToArray());
        exit(1);
    }
    waitpid(pid,&g_status()->status,0);
    return (g_status()->status);
}

void scan_cmd(t_execution *list)
{
    if (is_dir(list->args[0]))
    {
        g_status()->status = 126;
        print_error(list->args[0],": Is a directory");
    }
    else if (access(list->args[0],X_OK | F_OK) == 0)
        execute_cmd(list,list->args[0]);
    else
        perror(list->args[0]);
}

int is_valid(t_execution *list,char **path)
{
    int i = 0;
    char *tmp;
    char *full_cmd;
    while(path[i])
    {
        tmp = ft_strjoin(path[i], "/");
        full_cmd = ft_strjoin(tmp, list->args[0]);
        free(tmp);
        if (access(full_cmd,X_OK) == 0)
            return (execute_cmd(list,full_cmd));
        i++;
    }
    return (1);
}
void check_command_type(t_execution *list)
{
    int size;
    size = ft_lstsize(list);
    ft_execution(list,size);
}
void ft_execution(t_execution *list,int size)
{
    int i;
    char **path; 
    int pipes[2][2];
    pid_t *pid = malloc(sizeof(pid_t) * size);
    if (!pid)
        return ;
    path = get_path();
    while(i < size)
    {
        if (i < size - 1)
                pipe(pipes[i % 2]);
        if (path)
        {
            if (ft_strchr(list->args[0],'/'))
                scan_cmd(list);
            else if (is_dir(list->args[0]))
            {
                g_status()->status = 126;
                print_error(list->args[0],": command not found");
            }
            else if (is_valid(list,path) == 1)
                print_error(list->args[0],": command not found");
        }
        else
            scan_cmd(list);
        i++;
    }
}
