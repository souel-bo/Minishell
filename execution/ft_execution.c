#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/tokenizer.h"

int is_dir(char *path)
{
    struct stat buf;
    if (stat(path, &buf) == 0)
        return (S_ISDIR(buf.st_mode));
    return 0;
}

void print_error(char *name, char *error)
{
    ft_putstr_fd(name, 2);
    ft_putstr_fd(error, 2);
    ft_putchar_fd('\n', 2);
}

int execute_cmd(t_execution *list, char *cmd)
{
    if (ft_redirection(list->file) == 1)
        exit(1);
    else
        execve(cmd, list->args, listToArray());
    exit(1);
}

void scan_cmd(t_execution *list)
{
    if (is_dir(list->args[0]))
    {
        g_status()->status = 126;
        print_error(list->args[0], ": Is a directory");
    }
    else if (access(list->args[0], X_OK | F_OK) == 0)
        execute_cmd(list, list->args[0]);
    else
        perror(list->args[0]);
    exit(1);
}

int is_valid(t_execution *list, char **path)
{
    int i = 0;
    char *tmp;
    char *full_cmd;
    (void)path;
    char **paths = get_path();
    while (paths[i])
    {
        tmp = ft_strjoin(paths[i], "/");
        full_cmd = ft_strjoin(tmp, list->args[0]);
        free(tmp);
        if (access(full_cmd, X_OK) == 0)
            return (execute_cmd(list, full_cmd));
        i++;
    }
    ft_free(paths);
    return (1);
}
void check_command_type(t_execution *list)
{
    int size;
    size = ft_lstsize(list);
    ft_execution(list, size);
}
void cmdWpath(t_execution *list, char **path,int size)
{
    (void)path;

    if (if_builtin(list->args[0]) != 0)
        is_builtin(list->args[0],list,size);
    else if (ft_strchr(list->args[0], '/'))
            scan_cmd(list);
    else if (is_dir(list->args[0]))
    {
        print_error(list->args[0], ": command not found");
        g_status()->status = 126;
        exit(126);
    }
    else if (is_valid(list, path) == 1)
    {
        g_status()->status = 127;
        print_error(list->args[0], ": command not found");
        exit(127);
    }
}
void execute_pipeCmd(t_execution *list, t_hr hr,int size)
{
    if (search_in_env("PATH"))
        cmdWpath(list, hr.path,size);
    else
        scan_cmd(list);
}
void close_previous(int pipes[2][2], int i)
{
    if (i > 0)
    {
        close(pipes[(i + 1) % 2][1]);
        close(pipes[(i + 1) % 2][0]);
    }
}
void setup_pipes(int pipes[2][2], int i, int size)
{
    if (i > 0)
        dup2(pipes[(i + 1) % 2][0], STDIN_FILENO);
    if (i < size - 1)
        dup2(pipes[i % 2][1], STDOUT_FILENO);
    close_previous(pipes,i);
    if (i < size - 1)
    {
        close(pipes[i % 2][0]);
        close(pipes[i % 2][1]);
    }
}

void wait_all(pid_t *pids, t_hr hr)
{
    int j = 0;
    while (j < hr.i)
    {
        waitpid(pids[j], &g_status()->status, 0);
        j++;
    }
}
void execute_pipeline(int pipes[2][2], t_execution *list, t_hr helper, int size)
{
    (void)size;
    setup_pipes(pipes, helper.i, size);
    execute_pipeCmd(list, helper,size);
    exit(1);
}
void cleanup(pid_t *pid, t_hr hr)
{
    wait_all(pid, hr);
    // ft_free(hr.path);
    free(pid);
}
void execute_commands(t_execution *list, t_hr hr, int pipes[2][2], int size)
{
    if (size == 1)
    {
        if (search_in_env("PATH") == 1)
            cmdWpath(list, hr.path,size);
        else
            scan_cmd(list);
    }
    else
        execute_pipeline(pipes, list, hr, size);
}
void no_args(t_execution *list)
{
    int stdout_copy = dup(STDOUT_FILENO);
    int stdin_copy = dup(STDIN_FILENO);
    ft_redirection(list->file);  
    dup2(stdout_copy,1);
    dup2(stdin_copy,0);  
}
void check_builtin(t_execution *list, int size)
{
    int stdout_copy = dup(1);
    int stdin_copy = dup(0);
    if (size == 1)
    {
        if (list->file)
        {
            if (ft_redirection(list->file) == 0)
            {
                is_builtin(list->args[0], list,size);
                dup2(stdout_copy,1);
                dup2(stdin_copy,0);
            }
        }
        else
        {
            is_builtin(list->args[0], list,size);
            dup2(stdout_copy,1);
            dup2(stdin_copy,0);
        }
        close (stdout_copy);
        close (stdin_copy);
    }
}
void ft_execution(t_execution *list, int size)
{
    t_hr hr;
    hr.i = 0;
    int pipes[2][2];
    pid_t *pid = malloc(sizeof(pid_t) * size);
    while (hr.i < size)
    {
        if (list->args[hr.i] == NULL && list->file != NULL)
            no_args(list);
        else if (if_builtin(list->args[0]) != 0 && size == 1)
        {
            check_builtin(list,size);
            break;
        }
        else if (hr.i < size - 1)
            pipe(pipes[hr.i % 2]);
        pid[hr.i] = fork();
        if (pid[hr.i] == 0)
            execute_commands(list, hr, pipes, size);
        close_previous(pipes, hr.i);
        hr.i++;
        list = list->next;
    }
    cleanup(pid, hr);
    printf("%d\n",g_status()->status >> 8);
}
