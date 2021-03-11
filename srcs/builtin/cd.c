#include "../../includes/minishell.h"

int	set_directory(char *path)
{
	struct stat st;
	char	*pwd;
	char	*pwd_env;
	char	*old_pwd;

	pwd = getcwd(NULL, 0);
	pwd_env = get_env("PWD");
	old_pwd = !pwd_env ? pwd : pwd_env;
	if (!chdir(path))
	{
		set_env("OLDPWD", old_pwd);
		set_env("PWD", getcwd(NULL, 0));
		return (1);
	}
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_status = 1;
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd(": Aucun fichier ou dossier de ce type", 2);
		g_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory: ", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int			run_cd(char **args)
{
	char	*home;

	g_status = 0;
	home = get_env("HOME");
	if (!args[1] || ft_strequ(args[1], "~"))
	{
		if (!home)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		return (set_directory(home));
	}
	if (!args[1][0])
		return (set_directory("."));
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
