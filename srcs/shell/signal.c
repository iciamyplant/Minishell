/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:04:34 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/15 18:32:49 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	process(int sign_num)
{
	if (!kill(g_pid, sign_num))
	{
		if (sign_num == SIGQUIT)
		{
			ft_putstr_fd("Quit: 3\n", 1);
			g_status = 131;
		}
		else if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_status = 130;
		}
	}
	else if (sign_num == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_status = 1;
		prompt();
	}
}

void		sigint_handler(int sign_num)
{
	if ((sign_num == SIGINT || sign_num == SIGQUIT) && g_pid != 0)
		process(sign_num);
	else
	{
		if (sign_num == SIGINT)
		{
			ft_putchar_fd('\n', 1);
			g_status = 1;
			prompt();
		}
		else if (sign_num == SIGQUIT)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}
