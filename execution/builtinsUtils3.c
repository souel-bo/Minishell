#include "../includes/libft.h"
#include "../includes/minishell.h"
#include "../includes/tokenizer.h"

int	checkifnum(char *number)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if ((number[j] == '-') || (number[j] == '+'))
		j++;
	while (number[i])
	{
		if (number[j] >= 48 && number[j] <= 57)
			j++;
		i++;
	}
	if (j == i)
		return (1);
	return (0);
}
