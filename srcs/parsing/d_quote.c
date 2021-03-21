/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:31:52 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		d_quote(t_copy *copy, int j)
{
	if (copy->i == ((int)ft_strlen(copy->wc) - 1))
		return (quote_error('"'));
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '"')
	{
		j = 0;
		if (copy->wc[copy->i] == '$' && copy->wc[copy->i - 1] != '\\')
			j = env(copy, 0, 0, 0);
		if (copy->wc[copy->i] == '\\')
			if (copy->wc[copy->i + 1] == '$' || copy->wc[copy->i + 1] == '\\'
				|| copy->wc[copy->i + 1] == '"')
				copy->i++;
		if (j != 1)
			copy->cmd[++copy->j] = copy->wc[copy->i];
	}
	if (copy->wc[copy->i] == '"' && (copy->wc[copy->i + 1] == ' '
			|| copy->wc[copy->i + 1] == '\0') && !copy->cmd[0])
		copy->cmd[0] = '\0';
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '"')
		return (quote_error('"'));
	copy->i++;
	if (copy->cmd[0] == '\0' && (copy->wc[copy->i] == ' '
			|| copy->wc[copy->i] == '\0'))
		return (1);
	return (-2);
}

int		quote_util(t_copy *copy, int j, size_t i)
{
	if (copy->wc[copy->i] == '$' && copy->wc[copy->i - 1] != '\\')
	{
		j = env(copy, 1, i, 0);
		if (j == -2)
		{
			copy->i--;
			j = 1;
		}
	}
	if (copy->wc[copy->i] == '\\')
	{
		if (copy->wc[copy->i + 1] == '$' || copy->wc[copy->i + 1] == '\\'
			|| copy->wc[copy->i + 1] == '"')
			copy->i++;
	}
	return (j);
}

int		d_quote_arg(t_copy *copy, size_t i, int j)
{
	if (copy->i == ((int)ft_strlen(copy->wc) - 1))
		return (quote_error('"'));
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '"')
	{
		j = 0;
		j = quote_util(copy, j, i);
		if (j != 1)
			copy->args[i][++copy->j] = copy->wc[copy->i];
	}
	if (copy->wc[copy->i] == '"' && (copy->wc[copy->i + 1] == ' '
			|| copy->wc[copy->i + 1] == '\0') && !copy->args[i][0])
		copy->args[i][0] = '\0';
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '"')
		return (quote_error('"'));
	copy->i++;
	if (copy->args[i][0] == '\0' && (copy->wc[copy->i] == ' '
			|| copy->wc[copy->i] == '\0'))
		return (1);
	return (0);
}

int		quote_util_redir(t_copy *copy, char *str, int std, int j)
{
	while (copy->wc[copy->i] && copy->wc[++copy->i] != '"')
	{
		j = 0;
		if (copy->wc[copy->i] == '$' && (copy->i == 0
			|| copy->wc[copy->i - 1] != '\\'))
		{
			j = env_redir(copy, std, 0);
			if (j == -2)
			{
				copy->i--;
				j = 1;
			}
			if (copy->wc[copy->i] == '"' && copy->wc[copy->i - 1] != '\\')
				break ;
		}
		if (copy->wc[copy->i] == '\\')
		{
			if (copy->wc[copy->i + 1] == '$' || copy->wc[copy->i + 1] == '\\'
				|| copy->wc[copy->i + 1] == '"')
				copy->i++;
		}
		if (j != 1)
			str[++copy->redir.i] = copy->wc[copy->i];
	}
	return (j);
}

int		d_quote_redir(t_copy *copy, char *str, int std)
{
	if (copy->i == ((int)ft_strlen(copy->wc) - 1))
		return (quote_error('"'));
	if ((copy->wc[copy->i + 1] && copy->wc[copy->i + 1] == '"'
		&& copy->wc[copy->i + 2] == ' ')
		&& !str)
	{
		str[copy->redir.i] = ' ';
		str[copy->redir.i + 1] = 0;
		copy->i = copy->i + 2;
		return (-1);
	}
	if (quote_util_redir(copy, str, std, 0) != 0
		&& (copy->i == (int)ft_strlen(copy->wc) - 1))
		return (-1);
	if ((copy->i == (int)ft_strlen(copy->wc)) && copy->wc[copy->i] != '"')
		return (quote_error('"'));
	str[copy->redir.i + 1] = 0;
	copy->i++;
	if (copy->wc[copy->i] != ' ')
		return (1);
	return (-1);
}
