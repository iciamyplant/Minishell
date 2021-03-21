/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 03:45:58 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 04:13:39 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void		ft_exit(t_copy *copy, int i)
{
	free_cmdarg(copy);
	if (g_envs)
		ft_free_array(g_envs);
	if (copy->list)
		free_list(copy->list);
	if (copy->cmdssep)
		free(copy->cmdssep);
	if (!g_tester && i == 1)
		ft_putstr_fd("exit\n", 2);
	exit(g_status);
}

int			return_error(char *cmd, char *msg, int ret, int status)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(msg, 2);
	if (status >= 0)
		g_status = status;
	return (ret);
}

int			check_space_colon(char *line)
{
	size_t	i;
	int		colon;

	colon = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == ':' && colon)
			|| (!ft_isspace(line[i]) && line[i] != ':'))
			return (0);
		if (line[i] == ':')
			colon = 1;
		i++;
	}
	return (1);
}

void		prompt(void)
{
	char	*tmp;
	size_t	len;
	size_t	count_slash;

	if ((tmp = get_env("USER")))
	{
		ft_putstr_fd("\033[32;1m", 1);
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd("@\033[0m:", 1);
		free(tmp);
	}
	tmp = getcwd(NULL, 0);
	len = ft_strlen(tmp);
	count_slash = 0;
	while (--len && count_slash < 3)
		if (tmp[len] == '/')
			count_slash++;
	ft_putstr_fd("\e[1;34m", 1);
	while (tmp[++len])
		ft_putchar_fd(tmp[len], 1);
	ft_putstr_fd("$\e[0m ", 1);
	free(tmp);
}

int			main(int ac, char **av, char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		i++;
	if (!(g_envs = (char **)malloc(sizeof(char *) * (i + 1))))
		return (0);
	i = 0;
	while (env[i])
	{
		g_envs[i] = ft_strdup(env[i]);
		i++;
	}
	g_envs[i] = 0;
	if (ac >= 2)
	{
		if (av[1][0] == '-' && av[1][1] == 'c' && av[2])
			loop_tester(av[2]);
		else
			return_error(av[1], ": No such file or directory\n", 0, 127);
	}
	else
		loop();
	return (0);
}
