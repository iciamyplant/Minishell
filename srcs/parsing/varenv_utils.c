/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:42:06 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*remalloc_cmdargs(t_copy *copy, char *value, char *str)
{
	char	*tmp;
	int		j;

	j = -1;
	tmp = NULL;
	str[copy->j + 1] = 0;
	tmp = ft_strjoin(str, value);
	if (str)
		free(str);
	copy->j = -1;
	if (!(str = malloc(sizeof(char) * (ft_strlen(tmp) +
		ft_strlen(copy->wc) + 1))))
		return (NULL);
	while (tmp[++j])
		str[++copy->j] = tmp[j];
	if (tmp)
		free(tmp);
	return (str);
}

char	*remalloc_redir(t_copy *copy, char *value, char *str)
{
	char	*tmp;
	int		j;

	j = -1;
	tmp = NULL;
	str[copy->redir.i + 1] = 0;
	tmp = ft_strjoin(str, value);
	if (str)
		free(str);
	if (!(str = malloc(sizeof(char) * (ft_strlen(tmp) +
		ft_strlen(copy->wc) + 1))))
		return (NULL);
	while (tmp[++j])
		str[j] = tmp[j];
	str[j] = 0;
	if (tmp)
		free(tmp);
	copy->redir.i = ft_strlen(str) - 1;
	if (copy->i == (int)ft_strlen(copy->wc))
		copy->i++;
	return (str);
}

void	env_copy(t_copy *copy, int arg, int i, char *value)
{
	if (arg == 0)
		copy->cmd = remalloc_cmdargs(copy, value, copy->cmd);
	if (arg == 1)
		copy->args[i] = remalloc_cmdargs(copy, value, copy->args[i]);
	if (arg == 2)
		copy->redir.in = remalloc_redir(copy, value, copy->redir.in);
	if (arg == 3)
		copy->redir.out1 = remalloc_redir(copy, value, copy->redir.out1);
	if (arg == 4)
		copy->redir.out2 = remalloc_redir(copy, value, copy->redir.out2);
}

int		status_env(t_copy *copy, int arg, int i)
{
	char	*value;
	int		j;

	value = NULL;
	j = copy->i;
	if (arg >= 2 && j != (int)ft_strlen(copy->wc))
		j += 1;
	if (copy->wc[j] && (j < (int)ft_strlen(copy->wc))
		&& copy->wc[j] == '$' && copy->wc[j + 1] == '?')
	{
		if (j == 0 || (j > 0 && copy->wc[j - 1] != '\\'
			&& copy->wc[j - 1] != '$'))
		{
			value = ft_itoa(g_status);
			env_copy(copy, arg, i, value);
			if (value)
				free(value);
			copy->i++;
			return (1);
		}
	}
	return (0);
}

int		no_value(t_copy *copy, char *value)
{
	if (!value)
	{
		if (copy->wc[copy->i] == '"' || copy->wc[copy->i] == '\''
			|| copy->wc[copy->i] == '\\' || copy->wc[copy->i] == '|'
			|| copy->wc[copy->i] == '/' || copy->wc[copy->i] == '='
			|| copy->wc[copy->i] == ',' || copy->wc[copy->i] == ']'
			|| copy->wc[copy->i] == '[')
			copy->i--;
		if (copy->wc[copy->i] == ' ' && copy->wc[copy->i - 1] != '\\')
			return (-2);
		if (copy->wc[copy->i] == '$' && copy->wc[copy->i - 1] != '\\')
			copy->i--;
		return (1);
	}
	return (0);
}
