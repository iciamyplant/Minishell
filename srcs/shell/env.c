#include "../../includes/minishell.h"

ssize_t	find_env(char *env)
{
	char	*sub;
	ssize_t	i;
	ssize_t	index;

	if (!env)
		return (-1);
	i = 0;	
	sub = NULL;
	while (g_envs[i])
	{
		if ((index = ft_get_char_by_index(g_envs[i], '=')) == -1)
			index = ft_strlen(g_envs[i]);
		if ((sub = ft_substr(g_envs[i], 0, index)))
			if (ft_strequ(sub, env))
				return (i);
		i++;
	}
	return (-1);
}

char	*get_env(char *env)
{
	ssize_t	i;
	size_t	len;
	char	pwd[4096 + 1];
	char	*str;

	str = NULL;
	if (!env)
		return (NULL);
	len = ft_strlen(env);
	if ((i = find_env(env)) != -1)
		str = ft_substr(g_envs[i], (len + 1), ft_strlen(g_envs[i]));
	if (ft_strequ(env, "PWD") && (!str || !ft_strlen(str)))
	{
		if (getcwd(pwd, 4096))
			return ((str = ft_strdup(pwd)));
	}
	else if (i != -1)
		return (str);
	return (NULL);
}

char	*set_env(char *env, char *new_env)
{
	ssize_t	i;
	size_t	len;

	len = ft_strlen(env);
	i = -1;
	if ((i = find_env(env)) != -1)
	{
		if (!(g_envs[i] = ft_strjoin(ft_substr(g_envs[i], 0, len + 1), new_env)))
			return (NULL);
		return (g_envs[i]);
	}
	else
	{
		len = get_envs_count() + 1;
		g_envs = realloc_envs(len);
		g_envs[len - 1] = ft_strjoin(ft_strjoin(env, "="), new_env);
	}
	return (NULL);
}

char	**get_path()
{
	char	*path;

	if ((path = get_env("PATH")))
		return (ft_split(path, ':'));
	return (NULL);
}

size_t	get_envs_count()
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
//		g_envs[i] = NULL;
//		free(g_envs[i]);
		i++;
	}
	new[size] = 0;
//	free(g_envs);
	return (new);
}

void	print_envs()
{
	size_t	i;

	i = 0;
	while (g_envs[i])
	{
		ft_putendl_fd(g_envs[i], 1);
		i++;
	}
}