#include "minishell.h"
#include "LIBFT/libft.h"

void	ft_chdir(t_global *input)
{
	if (!input->split[1])
	{
		chdir(getenv("HOME"));
	}
	else
	{
		chdir(input->split[1]);
	}
}

void	ft_echo(t_global *input)
{
	int i;
	i = 1;
	int flag = 1;
	
	if (input->split[1])
	{
		if (strncmp(input->split[1], "-n", 2) == 0)
		{
			flag = 0;
			i++;
		}
	}
	if (input->split[i])
	{
		ft_putstr_fd(input->split[i], 1);
		{
			if (flag == 1)
				ft_putchar_fd('\n', 1);
		}
	}
}
void	ft_env(char **envp)
{
	int i = 0;
	while (envp[i])
	{
		ft_putstr_fd(envp[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
void	ft_exit(t_global *input)
{
	int status;
	status = 0;
	if (input->split[1])
	{
		status = ft_atoi(input->split[1]);
	}
	exit(status);
}
void	ft_pwd()
{
	char *buf;
	buf = malloc(sizeof(char) * 1024);
	if (!buf)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(1);
	}
	getcwd(buf, 1024);
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	free(buf);
}
