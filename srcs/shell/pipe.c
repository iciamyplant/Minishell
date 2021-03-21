/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:34:32 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:28:03 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		status_child(void)
{
	if (WIFEXITED(g_pid))
		g_status = WEXITSTATUS(g_pid);
	if (WIFSIGNALED(g_pid))
	{
		g_status = WTERMSIG(g_pid);
		if (g_status != 131)
			g_status += 128;
	}
}

static void	child(t_pip *pipcell, int fd[2], int *fdd)
{
	close(fd[0]);
	close(0);
	dup(*fdd);
	close(*fdd);
	if (pipcell->next)
	{
		close(1);
		dup(fd[1]);
		close(fd[1]);
	}
}

int			run_pipe(t_pip *pipcell, t_copy *cmdargs, int fdd)
{
	int		fd[2];

	fd[0] = -1;
	fd[1] = -1;
	if (pipe(fd))
		return (-1);
	g_pid = fork();
	if (g_pid < 0)
	{
		close(fd[0]);
		close(fd[1]);
		close(fdd);
		return (-1);
	}
	else if (!g_pid)
	{
		child(pipcell, fd, &fdd);
		execution(cmdargs, 1);
		ft_exit(cmdargs, 0);
	}
	wait(&g_pid);
	status_child();
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}
