#include "libft.h"

int only_spaces(char *str)
{
    int i = 0;
    while (str[i] == ' ')
        i++;
    if (i == (int)ft_strlen(str))
        return (1);
    return (0);
}