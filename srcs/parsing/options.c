#include "../../includes/minishell.h"

int	options_special_case(char *arg, char *whole_cmd, t_copy *copy)
{
	int		i;

	i = copy->i - 1;
	if (!arg[0] && (whole_cmd[copy->i - 1] == '"' || whole_cmd[copy->i - 1]
			== '\'') && (whole_cmd[copy->i - 2] == '"' || whole_cmd[copy->i - 2]
			== '\'') && !whole_cmd[copy->i])
	{
		while (whole_cmd[i] == '"' || whole_cmd[i] == '\'')
		{
			if (whole_cmd[i - 1] != whole_cmd[i])
				return (0);
			i = i - 2;
		}
		if (whole_cmd[i] != ' ')
			return (0);
		return (1);
	}
	return (0);
}

void	ft_copy_tmp(t_copy *copy, char **tmp, size_t j)
{
	while (j)
	{
		copy->args[j - 1] = ft_strdup(tmp[j - 1]);
		j--;
	}
}

int	options(char *whole_cmd, t_copy *copy, t_redir *redir, size_t i, size_t	j)
{
	char	**tmp;
	char	*arg;

	copy->args[0] = ft_strdup(copy->cmd);
	while (1)
	{
		tmp = copy->args;
		copy->args = (char **)malloc(sizeof(char *) * (i + 2));
		if (!(copy->args))
			return (-1);
		j = i;
		ft_copy_tmp(copy, tmp, j);
		arg = args(whole_cmd, copy, i, redir);
		if (g_error == -1)
			return (-1);
		if (options_special_case(arg, whole_cmd, copy) == 1)
			arg = args(whole_cmd, copy, ++i, redir);
		if ((!arg) || (!arg[0] && !whole_cmd[copy->i]))
			break ;
		i++;
	}
	copy->args[i] = NULL;
	return (1);
}
