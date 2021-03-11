#include "../../includes/minishell.h"

int	status_child(pid_t	g_pid)
{
	int		g_status;

	if (WIFEXITED(g_pid))
		g_status = WEXITSTATUS(g_pid);
	if (WIFSIGNALED(g_pid))
	{
		g_status = WTERMSIG(g_pid);
		if (g_status != 131)
			g_status += 128;
	}
	return (g_status);
}


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
		exit(g_status);
	}
	wait(&g_pid);
	g_status = status_child(g_pid);
	close(fdd);
	close(fd[1]);
	return (fd[0]);
}