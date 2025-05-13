#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
#include "../includes/libft.h"

void	ft_chdir(t_execution *input)
{
	if (!input->args[1])
	{
		if (search_in_env("HOME") == 1)
		{
			change_in_env("OLDPWD",getcwd(NULL,0));
			chdir(searchAndsave("HOME"));
			change_in_env("PWD",getcwd(NULL,0));
		}
		else
			printf("%s\n","cd: HOME not set");
	}
	else
	{
		change_in_env("OLDPWD",getcwd(NULL,0));
		chdir(input->args[1]);
		change_in_env("PWD",getcwd(NULL,0));
	}
}

void ft_echo(t_execution *input)
{
    int i = 1;
    int flag = 1;

    while (input->args[i] && strncmp(input->args[i], "-n", 2) == 0)
    {
        int j = 2;
        while (input->args[i][j] == 'n')
            j++;
        if (input->args[i][j] != '\0')
            break;
        flag = 0;
        i++;
    }
    while (input->args[i])
    {
        ft_putstr_fd(input->args[i], 1);
        if (input->args[i + 1])
            ft_putchar_fd(' ', 1);
        i++;
    }
    if (flag)
        ft_putchar_fd('\n', 1);
}