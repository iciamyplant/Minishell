/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip_extra_spaces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:59:45 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_without_extra_spaces(char *str)
{
	size_t		i;
	size_t		len;
	char		found_space;

	len = ft_strlen(str);
	if (str && (len) > 0)
		while ((len - 1) > 0 && str[len - 1] && ft_isspace(str[len - 1]))
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

void			copy(char **new, char *str, size_t i)
{
	size_t j;
	size_t k;

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

void			add_space_after(char *tmp, char *whole_cmd, int v, char **new)
{
	int i;
	int j;

	j = ft_strlen(*new);
	if (!tmp || ((i = (ft_strlen(tmp) - 1)) < 0))
		return ;
	if (tmp[i] == ' ' && follow_env(v, whole_cmd) && whole_cmd[v] == '$')
		return ;
	if (tmp[i] == ' ' && (whole_cmd[v] == '"' || whole_cmd[v] == '\'' ||
	whole_cmd[v] == '/' || whole_cmd[v] == '@' || whole_cmd[v] == ',' ||
	whole_cmd[v] == '$' || whole_cmd[v] == '[' || whole_cmd[v] == ']'
	|| whole_cmd[v] == '\\'))
	{
		(*new)[j] = ' ';
		(*new)[j + 1] = '\0';
	}
}

static char		*add(char *tmp, char *whole_cmd, int v, char *new)
{
	if (add_space_before(tmp, whole_cmd, v, &new) == -1)
	{
		if (tmp)
			free(tmp);
		return (new);
	}
	add_space_after(tmp, whole_cmd, v, &new);
	if (tmp)
		free(tmp);
	return (new);
}

char			*ft_strip_extra_spaces(char *str, char *whole_cmd, int v)
{
	char	*new;
	char	*tmp;
	size_t	i;
	size_t	k;
	size_t	len;

	tmp = NULL;
	tmp = ft_strdup(str);
	len = len_without_extra_spaces(str);
	if (!(new = (char *)malloc(sizeof(char) * (len + 3))))
	{
		if (tmp)
			free(tmp);
		return (NULL);
	}
	k = ft_strlen(str);
	if (str && (k) > 0)
		while ((k - 1) > 0 && str[k - 1] && ft_isspace(str[k - 1]))
			k--;
	str[k] = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	copy(&new, str, i);
	free(str);
	return (add(tmp, whole_cmd, v, new));
}
