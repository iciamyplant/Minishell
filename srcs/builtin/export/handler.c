#include "../../../includes/minishell.h"

static size_t	_len_without_extra_spaces(char *str)
{
	size_t	i;
	size_t	len;
	char	found_space;

	len = ft_strlen(str);
	while (str[len - 1] && ft_isspace(str[len - 1]))
		len--;
	str[len] = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	len -= i;
	i--;
	found_space = 0;
	while (str[++i])
		if (ft_isspace(str[i]) && !found_space)
			found_space = 1;
		else if (ft_isspace(str[i]))
			len--;
		else
			found_space = 0;
	return (len);
}

static char	*_strip_extra_spaces(char *str)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	len;

	len = _len_without_extra_spaces(str);
	if (!(new = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	k = ft_strlen(str);
	while (str[k - 1] && ft_isspace(str[k - 1]))
		k--;
	str[k] = '\0';
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	k = 0;
	j = 0;
	while (str[i])
	{
		if ((ft_isspace(str[i]) && !k && (k = 1)))
			new[j++] = str[i];
		else if (!ft_isspace(str[i]) && !(k = 0))
			new[j++] = str[i];
		i++;
	}
	new[j] = '\0';
	return (new);
}

static int	_check_name(char *args)
{
	size_t	i;
	char	alpha_found;

	i = 0;
	alpha_found = 0;
	if (!args || !args[0])
		return (0);
	while (args[i] && args[i] != '=')
	{
		if (ft_isalpha(args[i]))
			alpha_found = 1;
		else
		{
			if (ft_isdigit(args[i]) && !alpha_found)
				return (0);
			else if (!ft_isdigit(args[i]) && args[i] != '_')
				return (0);
		}
		i++;
	}
	return (1);
}

static int	set(char *arg, size_t equ, size_t index)
{
	char	*st;
	char	*end;
	ssize_t	equ_env;

	if (equ == ft_strlen(arg))
		return (0);
	if ((equ_env = ft_get_char_by_index(g_envs[index], '=')) == -1)
	{
		equ_env = ft_strlen(g_envs[index]);
		g_envs[index] = ft_strjoin(g_envs[index], "=");
	}
	if (!(st = ft_substr(g_envs[index], 0, (size_t)equ_env)))
		return (0);
	if (!(end = ft_substr(arg, equ + 1, ft_strlen(arg))))
		return (0);
	if (!(end = _strip_extra_spaces(end)))
		return (0);
	if (!(set_env(st, end)))
		return (0);
	return (1);
}

int	run_export(char **args)
{
	char	*strip;
	size_t	i;
	ssize_t	index;
	size_t	equal_index;
	size_t	count;

	g_status = 0;
	if (!args[1])
	{
		sort_env();
		return (1);
	}
	i = 0;
	while (args[++i])
	{
		if (!_check_name(args[i]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_status = 1;
			continue;
		}
		if ((equal_index = ft_get_char_by_index(args[i], '=')) == -1)
			equal_index = ft_strlen(args[i]);
		if ((index = find_env(ft_substr(args[i], 0, equal_index))) != -1)
			set(args[i], equal_index, index);
		else
		{
			count = get_envs_count() + 1;
			g_envs = realloc_envs(count);
			g_envs[count - 1] =	ft_strjoin(
				ft_substr(args[i], 0, ft_get_char_by_index(args[i], '=') + 1),
				_strip_extra_spaces(ft_substr(args[i], ft_get_char_by_index(args[i], '=') + 1, ft_strlen(args[i])))
			);
		}
	}
	return (1);
}