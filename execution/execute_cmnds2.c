#include "../includes/minishell.h"
#include "../includes/libft.h"
#include "../includes/tokenizer.h"

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