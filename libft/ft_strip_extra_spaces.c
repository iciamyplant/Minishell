#include "libft.h"
#include <stdio.h>

static size_t   _len_without_extra_spaces(char *str)
{
    size_t  i;
    size_t  len;
    char    found_space;

    len = ft_strlen(str);
    while (str[len - 1] && ft_isspace(str[len - 1]))
        len--;
    str[len] = '\0';
    i = 0;
    while (str[i] && ft_isspace(str[i]))
        i++;
    len -= i;
    i--;
    found_space = 0;
    while (str[++i])
    {
        if (ft_isspace(str[i]) && !found_space)
            found_space = 1;
        else if (ft_isspace(str[i]))
            len--;
        else
            found_space = 0;
    }
    return (len);
}

void	_copy(char **new, char *str, size_t i)
{
	size_t	j;
	size_t	k;

	k = 0;
    j = 0;
    while (str[i])
    {
        if ((ft_isspace(str[i]) && !k))
        {
            k = 1;
            (*new)[j++] = str[i];
        }
        else if (!ft_isspace(str[i]))
        {
            k = 0;
            (*new)[j++] = str[i];
        }
        i++;
    }
    (*new)[j] = '\0';
}

void    add_space_before(char *tmp, char *whole_cmd, int v, char **new)
{
    int i;
    int j;
    char *copy;
    
    i = 0;
    j = 0;
    copy = ft_strdup(*new);
    v--;
    if (tmp[i] == ' ')
    {
        while (whole_cmd[v] && whole_cmd[v] != '$' && whole_cmd[v - 1] != '\\')
            v--;
        if (whole_cmd[v - 1] == '"' || whole_cmd[v - 1] == '\'' || whole_cmd[v - 1] == '/' || whole_cmd[v - 1] == '@')
            while (copy[j])
            {
                (*new)[0] = ' ';
                (*new)[j + 1] = copy[j];
                j++;
            }
        //printf("il faut rajouter un esp devant\n");
    }
}

void    add_space_after(char *tmp, char *whole_cmd, int v, char **new)
{
    int     i;
    int     j;

    j = ft_strlen(*new);
    i = ft_strlen(tmp) - 1;
    if (tmp[i] == ' ' && (whole_cmd[v] == '"' || whole_cmd[v] == '\'' || whole_cmd[v] == '/' || whole_cmd[v] == '@'))
    {
        (*new)[j] = ' ';
        //printf("il faut rajouter un esp derriere\n");
    }
}

char *ft_strip_extra_spaces(char *str, char *whole_cmd, int v)
{
    char    *new;
    char    *tmp;
    size_t  i;
    size_t  k;
    size_t  len;

    //printf("whole_cmd[v - 1] = %c où v= %d\n", whole_cmd[v - 1], v);
    tmp = ft_strdup(str);
    len = _len_without_extra_spaces(str);
    new = (char *)malloc(sizeof(char) * (len + 3));
    if (!new)
        return (NULL);
    k = ft_strlen(str);
    while (str[k - 1] && ft_isspace(str[k - 1]))
        k--;
    str[k] = '\0';
    i = 0;
    while (str[i] && ft_isspace(str[i]))
        i++;
    _copy(&new, str, i);
    add_space_before(tmp, whole_cmd, v, &new);
    add_space_after(tmp, whole_cmd, v, &new);
    return (new);
}
