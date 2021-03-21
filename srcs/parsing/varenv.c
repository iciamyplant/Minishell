/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   varenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:37:14 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		multiple_dollars(t_copy *copy, int arg, int i)
{
	int		j;

	j = 0;
	while (copy->wc[copy->i] && copy->wc[copy->i] == '$' && (copy->wc
		[copy->i + 1] == '\0' || copy->wc[copy->i + 1] == '$' || (copy->i > 0
		&& copy->wc[copy->i - 1] == '$')))
	{
		if (arg == 0)
			copy->cmd[++copy->j] = copy->wc[copy->i];
		if (arg == 1)
			copy->args[i][++copy->j] = copy->wc[copy->i];
		copy->i++;
		if (ft_strlen(copy->wc) == 1 && copy->wc[0] == '$')
			return (1);
		j++;
	}
	if (j > 0)
	{
		copy->i--;
		return (1);
	}
	return (0);
}

int		find_name(t_copy *copy, int i, char **name)
{
	int		count;

	count = -1;
	if (i == 0)
		copy->i++;
	if (i == 0 && (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"'))
	{
		copy->i--;
		return (0);
	}
	while (copy->wc[copy->i] && (copy->wc[copy->i] != '\\' && copy->wc
		[copy->i] != ' ' && copy->wc[copy->i] != '$' && copy->wc[copy->i]
		!= ']' && copy->wc[copy->i] != '[' && copy->wc[copy->i] != '"' &&
		copy->wc[copy->i] != ',' && copy->wc[copy->i] != '\'' && copy->wc
		[copy->i] != '/' && copy->wc[copy->i] != '=' && copy->wc[copy->i] !=
		'|' && copy->wc[copy->i] != '@'))
	{
		if (i == 0 && (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"'))
			return (0);
		(*name)[++count] = copy->wc[copy->i];
		copy->i++;
	}
	(*name)[count + 1] = 0;
	return (1);
}

int		env(t_copy *copy, int arg, int i, int space)
{
	if (multiple_dollars(copy, arg, i) != 0 || status_env(
		copy, arg, i) == 1)
		return (1);
	if (init_value_name(copy) == -1)
		return (-1);
	if (find_name(copy, 0, &copy->redir.name) != 1)
	{
		free(copy->redir.name);
		return (0);
	}
	copy->redir.value = get_env(copy->redir.name);
	free(copy->redir.name);
	if (space == 1 && copy->redir.value)
		copy->redir.value = ft_strip_extra_spaces(copy->redir.value,
		copy->wc, copy->i);
	if ((space = no_value(copy, copy->redir.value)) != 0)
	{
		if (copy->redir.value)
			free(copy->redir.value);
		return (space);
	}
	env_copy(copy, arg, i, copy->redir.value);
	free(copy->redir.value);
	copy->i--;
	return (1);
}

void	env_redir_ambig(t_copy *copy, int spce)
{
	copy->redir.value = get_env(copy->redir.name);
	if (spce == 1 && copy->redir.value)
		copy->redir.value = ft_strip_extra_spaces(copy->redir.value,
		copy->wc, copy->i);
	if (copy->redir.value && spce == 1 && copy->wc[copy->i] != '$'
		&& (only_spaces(copy->redir.value)
		|| ft_space_in_middle(copy->redir.value)))
		error_ambiguous(copy->redir.name);
	if (!copy->redir.value && spce == 1 && copy->wc[copy->i] != '$')
		error_ambiguous(copy->redir.name);
	free(copy->redir.name);
}

int		env_redir(t_copy *copy, int std, int spce)
{
	int		count;

	if (init_value_name(copy) == -1)
		return (-1);
	copy->redir.name[0] = 0;
	copy->i++;
	if (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"')
	{
		free(copy->redir.name);
		return (0);
	}
	if (status_env(copy, std + 2, 0) == 1)
		return (1);
	find_name(copy, 1, &copy->redir.name);
	env_redir_ambig(copy, spce);
	if ((count = no_value(copy, copy->redir.value)) != 0)
	{
		if (copy->redir.value)
			free(copy->redir.value);
		return (count);
	}
	env_copy(copy, std + 2, 0, copy->redir.value);
	free(copy->redir.value);
	copy->i--;
	return (1);
}
