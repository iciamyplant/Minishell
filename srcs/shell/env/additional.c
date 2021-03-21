/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 21:53:21 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 02:57:19 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

ssize_t		find_env(char *env)
{
	char	*sub;
	ssize_t i;
	ssize_t index;

	if (!env)
		return (-1);
	i = 0;
	sub = NULL;
	while (g_envs[i])
	{
		if ((index = ft_get_char_by_index(g_envs[i], '=')) == -1)
			index = ft_strlen(g_envs[i]);
		if ((sub = ft_substr(g_envs[i], 0, index)))
		{
			if (ft_strequ(sub, env))
			{
				free(sub);
				return (i);
			}
			free(sub);
		}
		i++;
	}
	return (-1);
}

char		*get_env(char *env)
{
	ssize_t i;
	size_t	len;

	if (!env)
		return (NULL);
	len = ft_strlen(env);
	if ((i = find_env(env)) != -1)
		return (ft_substr(g_envs[i], (len + 1), ft_strlen(g_envs[i])));
	return (NULL);
}

static int	modify(char *new_env, size_t len, ssize_t i)
{
	char	*tmp;
	char	*new;

	if (!(tmp = ft_substr(g_envs[i], 0, (len + 1))))
		return (0);
	if (!(new = ft_strjoin(tmp, new_env)))
		return (0);
	free(g_envs[i]);
	free(tmp);
	g_envs[i] = new;
	return (1);
}

int			set_env(char *env, char *new_env)
{
	char	*tmp;
	ssize_t	i;
	size_t	len;

	if (!env || !new_env)
		return (0);
	len = ft_strlen(env);
	i = -1;
	if ((i = find_env(env)) != -1)
		return (modify(new_env, len, i));
	else
	{
		len = get_envs_count() + 1;
		g_envs = realloc_envs(len);
		tmp = ft_strjoin(env, "=");
		g_envs[len - 1] = ft_strjoin(tmp, new_env);
		free(tmp);
		return (1);
	}
	return (0);
}
