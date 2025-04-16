#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"
int	ft_lstsize(t_execution *lst)
{
	int	counter;

	counter = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		counter++;
	}
	return (counter);
}