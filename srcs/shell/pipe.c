#include "../../includes/minishell.h"

int    run_pipe(t_pip *pipcell, t_copy *cmdargs, int fdd, t_redir *redir)
{
	int		fd[2] = {-1, -1};

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
		close(fd[0]);
		close(0);
		dup(fdd);
		close(fdd);
	
		if (pipcell->next)
		{
			close(1);
			dup(fd[1]);
			close(fd[1]);
		}
		execution(cmdargs, redir, 1);
		exit(1);
	}
	wait(&g_pid);
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}