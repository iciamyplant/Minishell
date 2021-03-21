/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:30:59 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	redir_in_util(t_copy *copy, int i)
{
	if (i == 2)
	{
		if (copy->redir.out2)
			free(copy->redir.out2);
	}
	if (i == 1)
	{
		if (copy->redir.out1)
			free(copy->redir.out1);
	}
	else
	{
		copy->i++;
		if (copy->redir.in)
			free(copy->redir.in);
	}
}

int		redir_quoting(t_copy *copy, int i, char *file)
{
	if (copy->wc[copy->i] == '$' && copy->wc[copy->i - 1] != '\\')
		env_redir(copy, i, 1);
	while (copy->wc[copy->i] == '\'' || copy->wc[copy->i] == '"')
	{
		while (copy->wc[copy->i] == '"')
			if ((d_quote_redir(copy, file, i)) == -1)
			{
				if (create_file(copy, i) == -1)
					return (-1);
				return (4);
			}
		while (copy->wc[copy->i] == '\'')
			if ((s_quote_redir(copy, file)) == -1)
			{
				if (create_file(copy, i) == -1)
					return (-1);
				return (4);
			}
	}
	if (copy->wc[copy->i] == '\\')
		copy->i++;
	return (0);
}

int		redir_out_error(t_copy *copy, int i)
{
	redir_in_util(copy, 2);
	if (!(copy->redir.out2 = malloc(sizeof(char) * ft_strlen(copy->wc) + 1)))
		return (-1);
	while (copy->wc[copy->i] && copy->wc[copy->i] == ' ')
		copy->i++;
	while (copy->wc[copy->i] && copy->wc[copy->i] != ' ')
	{
		i = redir_quoting(copy, 2, copy->redir.out2);
		if (copy->i == (int)ft_strlen(copy->wc))
			break ;
		if (i != 0)
			return (i);
		if ((copy->wc[copy->i] == '<' || copy->wc[copy->i] == '>')
			&& (copy->wc[copy->i - 1] != '\\'))
		{
			copy->i--;
			break ;
		}
		copy->redir.out2[++copy->redir.i] = copy->wc[copy->i];
		copy->i++;
	}
	copy->redir.out2[copy->redir.i + 1] = 0;
	if (create_file(copy, 2) == -1)
		return (-1);
	return (1);
}

int		redir_out(t_copy *copy, int i)
{
	redir_in_util(copy, 1);
	if (!(copy->redir.out1 = malloc(sizeof(char) * ft_strlen(copy->wc) + 1)))
		return (-1);
	while (copy->wc[copy->i] && copy->wc[copy->i] == ' ')
		copy->i++;
	while (copy->wc[copy->i] && copy->wc[copy->i] != ' ')
	{
		i = redir_quoting(copy, 1, copy->redir.out1);
		if (copy->i == (int)ft_strlen(copy->wc))
			break ;
		if (i != 0)
			return (i);
		if ((copy->wc[copy->i] == '<' || copy->wc[copy->i] == '>')
			&& (copy->wc[copy->i - 1] != '\\'))
		{
			copy->i--;
			break ;
		}
		copy->redir.out1[++copy->redir.i] = copy->wc[copy->i];
		copy->i++;
	}
	copy->redir.out1[copy->redir.i + 1] = 0;
	if (create_file(copy, 1) == -1)
		return (-1);
	return (1);
}
