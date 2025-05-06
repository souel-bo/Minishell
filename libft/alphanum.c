#include "../includes/libft.h"
int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && (c <= 'Z')))
		return (1);
	return (0);
}
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
int	ft_isalnum(int c)
{
	if (ft_isdigit((unsigned char)c) || ft_isalpha((unsigned char)c))
		return (1);
	return (0);
}