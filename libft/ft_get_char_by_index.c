#include "libft.h"

size_t	ft_get_char_by_index(char *str, char c)
{
    char	*ch; 

	ch = ft_strchr(str, c);
	if (!ch)
        return (-1);
    return ((size_t)(ch - str));
}
