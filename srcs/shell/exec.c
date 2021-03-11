#include "../../includes/minishell.h"

static int	_run(char **args, char *bin, int pipe)
{	
	if (!pipe)
		g_pid = fork();
	if (pipe || !g_pid)
		execve(bin, args, g_envs);
	else if (!pipe && g_pid < 0)
	{
		free(bin);
		ft_putstr_fd("minishell: execve: failed to create a new process.", 2); // ?????
		ft_putchar_fd('\n', 1);
		g_status = 1;
		return (-1);
	}
	if (!pipe)
	{
		wait(&g_pid);
		if (WIFEXITED(g_pid))
		{
			//ft_putstr_fd("ca rentre 2\n", 2);
			g_status = WEXITSTATUS(g_pid);
		}
		if (WIFSIGNALED(g_pid))
		{
			//ft_putstr_fd("ca rentre 1\n", 2);
			g_status = WTERMSIG(g_pid);
			if (g_status != 131)
				g_status += 128;
		}
		//printf("g_pid = %d\n", g_pid);
		//printf("g_status = %d\n", g_status);
		g_pid = 0;
	}
	free(bin);
	return (1);
}

static int	_has_perm(char **args, char *bin, struct stat statbuf, int pipe)
{
	if (statbuf.st_mode & S_IFREG) // check if is not a folder.	
	{
		if (statbuf.st_mode & S_IXUSR) // check if the user can execute this file.
			return (_run(args, bin, pipe));
		else
		{
			ft_putstr_fd("minishell: execve: permission denied: ", 2);
			ft_putstr_fd(bin, 2);
			ft_putchar_fd('\n', 2);
			g_status = 1;
		}
		free(bin);
		return (1);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": is a directory\n", 2);
		g_status = 126;
	}
	free(bin);
	return (1);
}

static int	_check_bins(char **args, int pipe)
{
	struct stat	statbuf;
	char		**path;
	char		*bin;
	char		*tmp;
	size_t		i;

	if (!(path = ft_split(get_env("PATH"), ':')))
		return (-1);
	i = 0;
	while (path[i])
	{
		bin = ft_strjoin(path[i], "/");
		tmp = bin;
		bin = ft_strjoin(bin, args[0]);
		free(tmp);
		if (!lstat(bin, &statbuf))
		{
			ft_free_array(path);
			return (_has_perm(args, bin, statbuf, pipe));
		}
		else
			free(bin);
		i++;
	}
	ft_free_array(path);
	return (0);
}

static int	_check_builtin(char **args)
{
	char	*str;
	char	pwd[4096 + 1];

	if (ft_strequ(args[0], "echo"))
		return(run_echo(args));
	else if (ft_strequ(args[0], "cd"))
		return (run_cd(args));
	else if (ft_strequ(args[0], "unset"))
		return (run_unset(args));
	else if (ft_strequ(args[0], "export"))
		return (run_export(args));
	else if (ft_strequ(args[0], "exit"))
		run_exit(args);
	else if (ft_strequ(args[0], "pwd"))
	{
		if ((str = getcwd(pwd, 4096)))
		{
			ft_putstr_fd(str, 1);
			ft_putchar_fd('\n', 1);
			return (1);
		}
	}
	else if (ft_strequ(args[0], "env"))
	{
		run_env();
		return (1);
	}
	return (0);
}

int			exec(char **args, t_redir *redir, int pipe)
{
	struct stat	f;
	int			is_cmd;

	g_pid = 0;
	if ((!args || !args[0] || args[0][0] == '\0') && !args[1])
		return (1);
	is_cmd = _check_builtin(args) || _check_bins(args, pipe);
	if (is_cmd > 0)
		return (1);
	else if (is_cmd < 0)
		return (-1);
	if (lstat(args[0], &f) != -1)
	{
		if (f.st_mode & S_IFDIR)
		{
			if (!ft_strncmp(args[0], "./", 2))
			{
				ft_putstr_fd("minishell: ", 2);
				ft_putstr_fd(args[0], 2);
				ft_putstr_fd(": is a directory\n", 2);
				g_status = 126;
			}
			else
				set_directory(args[0]);
			return (0);
		}
		else if ((f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR))
			return (_run(args, ft_strdup(args[0]), pipe));
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(args[0], 2);
			if (ft_strequ(args[0], "_") && (g_status = 127))
				ft_putstr_fd(": command not found\n", 2);
			else
			{
				ft_putstr_fd(": Permission denied\n", 2);
				g_status = 126;
			}
			return (0);
		}
	}
	else if (!ft_strncmp(args[0], "./", 2))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": Aucun fichier ou dossier de ce type\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	g_status = 127;
	//ft_putstr_fd("g_status = 127\n", 2);
	return (0);
}
