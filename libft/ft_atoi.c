#include "../includes/libft.h"

int ft_atoi(char *str)
{
    int i;
    int sign;
    long result;

    i = 0;
    sign = 1;
    result = 0;
    if (!str)
        return (0);
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\f' || str[i] == '\v')
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        if ((result > (INT_MAX - str[i] - '0') / 10))
            return (-1);        
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}