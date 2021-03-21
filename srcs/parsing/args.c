/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:32:41 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		init_malloc_args(t_copy *copy, size_t i)
{
	copy->j = -1;
	copy->args[i] = NULL;
	copy->args[i] = malloc(sizeof(char) * ((ft_strlen(copy->wc) + 1)));
	if (!(copy->args[i]))
		return (-1);
	copy->args[i][0] = 0;
	while (copy->wc[copy->i] && copy->wc[copy->i] == ' ')
		copy->i++;
	copy->i--;
	return (0);
}

int		args_quoting(t_copy *copy, int j, size_t i)
{
	if ((copy->wc[copy->i] == '1' || copy->wc[copy->i] == '2') && copy->wc
		[copy->i + 1] == '>' && copy->wc[copy->i - 1] == ' ')
		copy->i++;
	while (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"')
	{
		while (copy->wc[copy->i] == '"')
		{
			j = d_quote_arg(copy, i, 0);
			if (j == -1)
				return (-1);
		}
		while (copy->wc[copy->i] == '\'')
		{
			if ((s_quote_arg(copy, i)) == -1)
				return (-1);
		}
	}
	if (copy->wc[copy->i] == '\\' && copy->i == (int)ft_strlen(copy->wc)
		- 1 && copy->wc[copy->i - 1] != '\\')
		return (j);
	if (copy->wc[copy->i] == '\\')
		copy->i++;
	return (j);
}

int		args_redir_env(t_copy *copy, int j, size_t i)
{
	if (copy->wc[copy->i] && copy->wc[copy->i] == '$'
		&& copy->wc[copy->i - 1] != '\\')
	{
		if (copy->wc[copy->i + 1] == '\\')
			copy->args[i][++copy->j] = copy->wc[copy->i];
		else
			j = env(copy, 1, i, 1);
	}
	if ((copy->wc[copy->i] == '>' || copy->wc[copy->i] == '<')
		&& copy->wc[copy->i - 1] != '\\')
		j = redirection(copy, 0);
	return (j);
}

void	copy_arg(t_copy *copy, size_t i, int j)
{
	if (copy->wc[copy->i] && (copy->wc[copy->i] != ' ' || (copy->wc
				[copy->i] == ' ' && copy->wc[copy->i - 1] == '\\'))
		&& j != 1 && j != 4 && ((copy->wc[copy->i] == '$'
				&& copy->wc[copy->i - 1] == '\\')
			|| (copy->wc[copy->i] != '$')))
		copy->args[i][++copy->j] = copy->wc[copy->i];
}

char	*args(t_copy *copy, size_t i, int j)
{
	if (init_malloc_args(copy, i) == -1)
		return (NULL);
	while (copy->wc[copy->i] && (copy->wc[++copy->i] != ' '
			|| (copy->wc[copy->i] == ' ' && copy->wc[copy->i - 1] == '\\')))
	{
		j = 0;
		j = args_quoting(copy, j, i);
		j = args_redir_env(copy, j, i);
		if (j == -3)
		{
			copy->args[i][copy->j + 1] = 0;
			return (copy->args[i]);
		}
		if ((copy->wc[copy->i] == ' ' && copy->wc[copy->i - 1] != '\\')
			&& (copy->args[i][0] || (!copy->args[i][0] && (copy->wc
						[copy->i - 1] == '"' || copy->wc[copy->i - 1] == '\'')
					&& (copy->wc[copy->i - 2] == '"' || copy->wc
						[copy->i - 2] == '\'' || j == 1))))
		{
			break ;
		}
		copy_arg(copy, i, j);
	}
	copy->args[i][copy->j + 1] = 0;
	return (copy->args[i]);
}
