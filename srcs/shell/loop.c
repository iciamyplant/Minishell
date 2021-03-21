/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 04:10:04 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 04:24:29 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	init(t_copy *cmdarg)
{
	size_t	i;
	char	*tmp;

	ft_bzero(cmdarg, sizeof(t_copy));
	tmp = get_env("SHLVL");
	i = (ft_atoi(tmp) + 1);
	free(tmp);
	tmp = ft_itoa(i);
	signal(SIGQUIT, sigint_handler);
	signal(SIGINT, sigint_handler);
	set_env("SHLVL", tmp);
	free(tmp);
	prompt();
	g_pid = 0;
	g_tester = 0;
}

static void	start(t_copy *cmdarg, char *line)
{
	size_t	i;

	cmdarg->cmdssep = ft_minishell_split(line, ';');
	free(line);
	i = -1;
	while (cmdarg->cmdssep[++i])
		cmdarg->list = add_cell(cmdarg->list, cmdarg->cmdssep[i], i);
	parse_pip(cmdarg->list);
	minishell(cmdarg->list, cmdarg);
	if (cmdarg->list)
	{
		free_list(cmdarg->list);
		cmdarg->list = NULL;
	}
	if (cmdarg->cmdssep)
	{
		free(cmdarg->cmdssep);
		cmdarg->cmdssep = NULL;
	}
}

void		loop(void)
{
	t_copy	cmdarg;
	char	*line;

	init(&cmdarg);
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		cmdarg.list = NULL;
		cmdarg.cmdssep = NULL;
		signal(SIGINT, sigint_handler);
		if (check_space_colon(line))
		{
			free(line);
			prompt();
			continue;
		}
		if (syntax_error(line, '|', 0) != -1 && syntax_error(line, ';',
			0) != -1)
			start(&cmdarg, line);
		else
			free(line);
		prompt();
	}
	ft_exit(&cmdarg, 1);
}

void		free_tester(t_copy *cmdarg)
{
	if (cmdarg->list)
	{
		free_list(cmdarg->list);
		cmdarg->list = NULL;
	}
	if (cmdarg->cmdssep)
	{
		free(cmdarg->cmdssep);
		cmdarg->cmdssep = NULL;
	}
}

void		loop_tester(char *line)
{
	t_copy	cmdarg;
	size_t	i;

	g_tester = 1;
	ft_bzero(&cmdarg, sizeof(t_copy));
	if (check_space_colon(line))
		ft_exit(&cmdarg, 1);
	cmdarg.list = NULL;
	i = -1;
	if (syntax_error(line, '|', 0) != -1 && syntax_error(line, ';', 0) != -1)
	{
		cmdarg.list = NULL;
		cmdarg.cmdssep = NULL;
		cmdarg.cmdssep = ft_minishell_split(line, ';');
		while (cmdarg.cmdssep[++i])
			cmdarg.list = add_cell(cmdarg.list, cmdarg.cmdssep[i], i);
		parse_pip(cmdarg.list);
		minishell(cmdarg.list, &cmdarg);
		free_tester(&cmdarg);
	}
	ft_exit(&cmdarg, 1);
}
