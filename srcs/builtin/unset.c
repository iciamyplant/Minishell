/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:33:10 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/14 16:45:50 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	**remove_env(ssize_t index)
{
	char	*tmp;
	size_t	i;
	size_t	size;

	i = index;
	size = get_envs_count();
	while (g_envs[i + 1])
	{
		tmp = ft_strdup(g_envs[i + 1]);
		free(g_envs[i]);
		g_envs[i] = tmp;
		i++;
	}
	return (realloc_envs((size - 1)));
}

int			run_unset(char **args)
{
	size_t	i;
	ssize_t	index;

	g_status = 0;
	if (!args[1])
		return (1);
	i = 0;
	while (args[++i])
	{
		index = find_env(args[i]);
		if (index != -1)
		{
			if (g_envs[index])
				g_envs = remove_env(index);
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_status = 1;
		}
	}
	return (1);
}
