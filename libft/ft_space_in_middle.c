#include "libft.h"

int ft_space_in_middle(char *str)
{
    int i = 0;
    while (str[i] == ' ')
        i++;
    while (str[i] && str[i] != ' ')
        i++;
    while (str[i] == ' ')
    {
        i++;
        if (str[i] && str[i] != ' ')
            return (1);
    }
    return (0);
}
