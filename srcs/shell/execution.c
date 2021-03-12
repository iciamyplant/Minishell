#include "../../includes/minishell.h"

void	minishell(t_sep *list)
{
	int		fdd;
	t_copy	cmdarg;
	t_redir	redir;
	int 	i;

	fdd = dup(0);
	i = 0;
	while (list)
	{
		if (list->pipcell != NULL)
		{
			while (list->pipcell)
			{
				if (parsing(list->pipcell->cmd_pip, &cmdarg, &redir) == NULL)
					break;
//				print_parsing(cmdarg.args, &redir);
				fdd = run_pipe(list->pipcell, &cmdarg, fdd, &redir);
				list->pipcell = list->pipcell->next;
			}
    		close(fdd);
		}
		else
		{
			if (parsing(list->cmd_sep, &cmdarg, &redir) == NULL)
				break;
			print_parsing(cmdarg.args, &redir);
			execution(&cmdarg, &redir, 0);
			//printf("ca passe dans execution\n");
		}
		list = list->next;
		i++;
	}
}

void	redir_dup(t_copy *cmdarg, t_redir *redir, int pipe)
{
	int		savein;
	int		saveout1;
	int		saveout2;

	if (redir->in)
	{
		savein = dup(0);
		close(0);
		dup2(redir->sstdin, 0);
	}
	if (redir->out1)
	{
		saveout1 = dup(1);
		close (1);
		dup2(redir->sstdout, 1);
	}
	if (redir->out2)
	{
		saveout2 = dup(2);
		close (2);
		dup2(redir->sstderr, 2);
	}
	exec(cmdarg->args, redir, 0);
	if (redir->in)
		dup2(savein, 0);
	if (redir->out1)
		dup2(saveout1, 1);
	if (redir->out2)
		dup2(saveout2, 2);
}

void	execution(t_copy *cmdarg, t_redir *redir, int pipe)
{
	if (redir->in || redir->out1 || redir->out2)
		redir_dup(cmdarg, redir, pipe);
	else
		exec(cmdarg->args, redir, pipe);	
}
