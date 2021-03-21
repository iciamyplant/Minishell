/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:28:17 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/15 20:00:17 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	check(char **args, int pipe)
{
	struct stat	f;
	int			flag;

	if (lstat(args[0], &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR && (args[0][ft_strlen(args[0]) - 1] == '/'
				|| ft_strnequ(args[0], "./", 2)))
			return (return_error(args[0], ": Is a directory\n", 0, 126));
		else if ((ft_strnequ(args[0], "./", 2) || ft_strnequ(args[0], "/", 1))
			&& (f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR))
			return (run(args, ft_strdup(args[0]), pipe));
		else if (flag != S_IXUSR && flag != S_IRUSR
			&& flag != S_IFDIR && flag != S_IFLNK)
			return (return_error(args[0], ": Permission denied\n", 0, 126));
	}
	else if (ft_strnequ(args[0], "./", 2) || args[0][0] == '/')
	{
		return (return_error(args[0], ": No such file or directory\n", 0, 127));
	}
	return (return_error(args[0], ": command not found\n", 0, 127));
}

int			exec(char **args, int pipe, t_copy *copy)
{
	char		*path;
	int			is_cmd;

	g_pid = 0;
	if ((!args || !args[0] || args[0][0] == '\0') && !args[1])
		return (1);
	path = get_env("PATH");
	if (ft_strequ(args[0], "whoami") && !path)
		return (return_error(args[0], ": No such file or directory\n", 0, 127));
	free(path);
	is_cmd = check_builtin(args, copy) || check_bins(args, pipe);
	if (is_cmd > 0)
		return (1);
	else if (is_cmd < 0)
		return (-1);
	check(args, pipe);
	return (0);
}
