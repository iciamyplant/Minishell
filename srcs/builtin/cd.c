#include "../../includes/minishell.h"

int	set_directory(char *path)
{
	struct stat st;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		set_env("OLDPWD", pwd);
		set_env("PWD", getcwd(NULL, 0));
		return (1);
	}
	ft_putstr_fd("cd: ", 2);
	code = 1;
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		code = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd("permission denied: ", 2);		
	else
		ft_putstr_fd("not a directory: ", 2);
	ft_putstr_fd(path, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int			run_cd(char **args)
{
	char	*home;

	code = 0;
	home = get_env("HOME");
	if (!args[1] || ft_strequ(args[1], "~"))
		return (set_directory(home));
	if (!args[1][0])
		return (1);
	if (!ft_strcmp(args[1], "-"))
	{
		set_directory(get_env("OLDPWD"));
		ft_putstr_fd(get_env("PWD"), 1);
		ft_putchar_fd('\n', 1);
		return (1);
	}
	else if (!ft_strcmp(args[1], "--"))
		return (set_directory(home));
	else
		return (set_directory(args[1]));
	return (0);
}