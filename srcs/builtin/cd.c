/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:29:42 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 13:16:01 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_home_path(char *path)
{
	char		*tmp;
	char		*tmpp;

	if (!ft_strncmp(path, "~/", 2))
	{
		if ((tmp = get_env("HOME")))
		{
			tmpp = ft_substr(path, 1, ft_strlen(path));
			free(path);
			path = ft_strjoin(tmp, tmpp);
			free(tmpp);
			free(tmp);
			return (path);
		}
	}
	return (path);
}

static int	change(char *path, int home)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!chdir(path))
	{
		if (pwd)
		{
			set_env("OLDPWD", pwd);
			free(pwd);
		}
		if ((pwd = getcwd(NULL, 0)))
		{
			set_env("PWD", pwd);
			free(pwd);
		}
		if (home)
			free(path);
		return (1);
	}
	free(pwd);
	return (0);
}

int			set_directory(char *path, int home)
{
	struct stat	st;

	if (change(path, home))
		return (1);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	g_status = 1;
	if (stat(path, &st) == -1)
	{
		ft_putstr_fd(": No such file or directory", 2);
		g_status = 127;
	}
	else if (!(st.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied", 2);
	else
		ft_putstr_fd(": Not a directory", 2);
	ft_putchar_fd('\n', 2);
	if (home)
		free(path);
	return (1);
}

int			s_path(char **args)
{
	char *tmp;

	if (ft_strequ(args[1], "-"))
	{
		if ((tmp = get_env("OLDPWD")))
		{
			set_directory(tmp, 0);
			free(tmp);
		}
		if ((tmp = get_env("PWD")))
		{
			ft_putstr_fd(tmp, 1);
			free(tmp);
			ft_putchar_fd('\n', 1);
		}
		return (1);
	}
	return (set_directory(args[1], 0));
}

int			run_cd(char **args)
{
	char	*home;

	g_status = 0;
	home = NULL;
	if (args && args[1] && args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (!args[1] || ft_strequ(args[1], "~") || ft_strequ(args[1], "--"))
	{
		if (!(home = get_env("HOME")))
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			return (1);
		}
		return (set_directory(home, 1));
	}
	args[1] = add_home_path(args[1]);
	return (s_path(args));
}
