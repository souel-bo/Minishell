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
	while (input->split[i])
	{
		ft_putstr_fd(input->split[i], 1);
		if (flag == 1 && input->split[i + 1] == NULL)
			ft_putchar_fd('\n', 1);
		if (input->split[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
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
	buf = getcwd(NULL, 0);
	if (!buf)
	{
		ft_putstr_fd("malloc failed\n", 2);
		exit(1);
	}
	ft_putstr_fd(buf, 1);
	ft_putchar_fd('\n', 1);
	free(buf);
}

void	ft_export_unset(t_global *input, char ***envp)
{
	int i = 0;
	int j = 0;
	int	len_of_envp;
	char **new_envp;

	len_of_envp = count_2D(*envp);
	if (!input->split[1])
		return ;
	else if (!ft_strncmp(input->split[0], "unset", 5) && input->split[0][5] == '\0')
		{
			new_envp = malloc(sizeof(char *) * (len_of_envp));
			if (!new_envp)
				exit(1);
			while ((*envp)[i])
			{
				if (!(ft_strncmp((*envp)[i], input->split[1], ft_strlen(input->split[1])) == 0 && (*envp)[i][ft_strlen(input->split[1])] == '='))
				{
				    new_envp[j] = ft_strdup((*envp)[i]);
					if (!new_envp[j])
						exit(1);
	    			j++;
				}
				i++;
			}
			new_envp[j] = NULL;
			// ft_free_split(*envp);
			*envp = new_envp;
			j = 0;
			while (new_envp[j])
			{
				ft_putstr_fd(new_envp[j], 1);
				ft_putchar_fd('\n', 1);
				j++;
			}
		}
} 
