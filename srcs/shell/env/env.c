/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:48:24 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:10:18 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	**get_path(void)
{
	char	**path;
	char	*tmp;

	if (!(tmp = get_env("PATH")))
		return (NULL);
	if (!(path = ft_split(tmp, ':')))
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (path);
}

size_t	get_envs_count(void)
{
	size_t	count;

	count = 0;
	while (g_envs[count])
		count++;
	return (count);
}

char	**realloc_envs(size_t size)
{
	char	**new;
	size_t	i;

	if (!(new = (char **)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (g_envs[i] && i < size)
	{
		new[i] = ft_strdup(g_envs[i]);
		i++;
	}
	new[size] = 0;
	ft_free_array(g_envs);
	return (new);
}

void	print_envs(void)
{
	size_t	i;

	i = 0;
	while (g_envs[i])
	{
		ft_putendl_fd(g_envs[i], 1);
		i++;
	}
}
