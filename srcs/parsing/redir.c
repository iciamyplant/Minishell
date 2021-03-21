/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:38:54 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	create_file_out2(t_copy *copy)
{
	if (!copy->redir.out2[0])
		return (error_exit(copy->redir.out2, "No such file or directory"));
	if (copy->redir.end == 1)
		copy->redir.sstderr = open(copy->redir.out2, O_CREAT | O_RDWR |
			O_APPEND, 0644);
	else
		copy->redir.sstderr = open(copy->redir.out2, O_CREAT | O_RDWR |
			O_TRUNC, 0644);
	if (copy->redir.sstderr == -1)
		return (error_exit(copy->redir.out2, "No such file or directory"));
	return (0);
}

int	create_file_in(t_copy *copy)
{
	copy->redir.sstdin = open(copy->redir.in, O_RDONLY);
	if (!copy->redir.in[0] || copy->redir.sstdin == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(copy->redir.in, 2);
		ft_putstr_fd(": No such file or directory", 2);
	}
	g_status = 1;
	g_error = 1;
	return (0);
}

int	create_file(t_copy *copy, int type)
{
	errno = 0;
	if (type == 1)
	{
		if (!copy->redir.out1[0])
			return (error_exit(copy->redir.out1, "No such file or directory"));
		if (copy->redir.end == 1)
			copy->redir.sstdout = open(copy->redir.out1, O_CREAT | O_RDWR
				| O_APPEND, 0644);
		else
			copy->redir.sstdout = open(copy->redir.out1, O_CREAT | O_RDWR
				| O_TRUNC, 0644);
		if (copy->redir.sstdout == -1)
			return (error_exit(copy->redir.out1, "No such file or directory"));
	}
	if (type == 2)
		return (create_file_out2(copy));
	if (type == 0)
		return (create_file_in(copy));
	return (0);
}

int	redir_in(t_copy *copy, int i)
{
	redir_in_util(copy, 0);
	if (!(copy->redir.in = malloc(sizeof(char) * ft_strlen(copy->wc) + 1)))
		return (-1);
	while (copy->wc[copy->i] && copy->wc[copy->i] == ' ')
		copy->i++;
	while (copy->wc[copy->i] && copy->wc[copy->i] != ' ')
	{
		i = redir_quoting(copy, 0, copy->redir.in);
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
		copy->redir.in[++copy->redir.i] = copy->wc[copy->i];
		copy->i++;
	}
	copy->redir.in[copy->redir.i + 1] = 0;
	if (create_file(copy, 0) == -1)
		return (-1);
	return (1);
}

int	redirection(t_copy *copy, int i)
{
	copy->redir.i = -1;
	if (copy->wc[copy->i] == '>')
	{
		copy->redir.end = 0;
		copy->i++;
		if (copy->wc[copy->i] == '>')
		{
			copy->redir.end = 1;
			copy->i++;
		}
		if ((copy->redir.end == 0 && (copy->i == 2 || (copy->i > 3
			&& copy->wc[copy->i - 2] == '2' && copy->wc[copy->i - 3] == ' ')))
			|| (copy->redir.end == 1 && (copy->i == 3 || (copy->i > 4
			&& copy->wc[copy->i - 3] == '2'
			&& (copy->wc[copy->i - 4] == ' ')))))
			i = redir_out_error(copy, 0);
		else
			i = redir_out(copy, 0);
	}
	if (copy->wc[copy->i] == '<')
		i = redir_in(copy, 0);
	if (copy->i >= (int)ft_strlen(copy->wc))
		return (-3);
	return (i);
}
