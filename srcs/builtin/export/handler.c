/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 02:26:36 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 02:32:54 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static int	sub_free(char *st, char *end)
{
	if (set_env(st, end))
	{
		free(st);
		free(end);
		return (0);
	}
	free(st);
	free(end);
	return (1);
}

static int	set(char *arg, size_t equ, size_t index)
{
	char	*st;
	char	*end;
	ssize_t	equ_env;

	if (equ == ft_strlen(arg))
		return (0);
	equ_env = ft_get_char_by_index(g_envs[index], '=');
	if (equ_env == -1)
	{
		equ_env = ft_strlen(g_envs[index]);
		st = g_envs[index];
		g_envs[index] = ft_strjoin(g_envs[index], "=");
		free(st);
	}
	st = ft_substr(g_envs[index], 0, (size_t)equ_env);
	if (!st)
		return (0);
	end = ft_substr(arg, (equ + 1), ft_strlen(arg));
	return (sub_free(st, end));
}

static void	modify(char **args, char *st, size_t i)
{
	char	*end;
	size_t	count;

	end = NULL;
	count = get_envs_count() + 1;
	g_envs = realloc_envs(count);
	if (!(st = ft_substr(args[i], 0,
		ft_get_char_by_index(args[i], '=') + 1)))
		return ;
	if (!(end = ft_substr(args[i],
		ft_get_char_by_index(args[i], '=') + 1, ft_strlen(args[i]))))
	{
		free(st);
		return ;
	}
	g_envs[count - 1] = ft_strjoin(st, end);
	free(st);
	free(end);
}

static void	add(char **args, size_t i)
{
	ssize_t	index;
	size_t	equal_index;
	char	*st;

	equal_index = ft_get_char_by_index(args[i], '=');
	if (equal_index == (size_t)-1)
		equal_index = ft_strlen(args[i]);
	st = ft_substr(args[i], 0, equal_index);
	index = find_env(st);
	free(st);
	if (index != -1)
		set(args[i], equal_index, index);
	else
		modify(args, st, i);
}

int			run_export(char **args)
{
	size_t	i;

	g_status = 0;
	if (!args[1])
	{
		sort_env();
		return (1);
	}
	i = 0;
	while (args[++i])
	{
		if (!check_export_name(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_status = 1;
			continue ;
		}
		add(args, i);
	}
	return (1);
}
