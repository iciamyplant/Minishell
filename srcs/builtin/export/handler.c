#include "../../../includes/minishell.h"

static int	_set(char *arg, size_t equ, size_t index)
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
		g_envs[index] = ft_strjoin(g_envs[index], "=");
	}
	st = ft_substr(g_envs[index], 0, (size_t)equ_env);
	if (!st)
		return (0);
	end = ft_substr(arg, equ + 1, ft_strlen(arg));
	if (!end)
		return (0);
	if (!(set_env(st, end)))
		return (0);
	return (1);
}

static int	_add(char **args, size_t i)
{
	ssize_t	index;
	size_t	equal_index;
	size_t	count;

	equal_index = ft_get_char_by_index(args[i], '=');
	if (equal_index == -1)
		equal_index = ft_strlen(args[i]);
	index = find_env(ft_substr(args[i], 0, equal_index));
	if (index != -1)
		_set(args[i], equal_index, index);
	else
	{
		count = get_envs_count() + 1;
		g_envs = realloc_envs(count);
		g_envs[count - 1] = ft_strjoin(
				ft_substr(args[i], 0,
					ft_get_char_by_index(args[i], '=') + 1),
						ft_substr(args[i],
						ft_get_char_by_index(args[i], '=') + 1,
						ft_strlen(args[i]))
				);
	}
	return (1);
}

int	run_export(char **args)
{
	char	*strip;
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
		_add(args, i);
	}
	return (1);
}
