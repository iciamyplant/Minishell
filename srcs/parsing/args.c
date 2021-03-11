#include "../../includes/minishell.h"

int	init_malloc_args(char *whole_cmd, t_copy *copy, size_t i)
{
	copy->j = -1;
	copy->args[i] = NULL;
	copy->args[i] = malloc(sizeof(char) * (strlen(whole_cmd) + 1));
	if (!(copy->args[i]))
		return (-1);
	copy->args[i][0] = 0;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	copy->i--;
	return (0);
}

int	args_quoting(char *whole_cmd, t_copy *copy, int j, size_t i)
{
	if ((whole_cmd[copy->i] == '1' || whole_cmd[copy->i] == '2') && whole_cmd
		[copy->i + 1] == '>' && whole_cmd[copy->i - 1] == ' ')
		copy->i++;
	while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
	{
		while (whole_cmd[copy->i] == '"')
		{
			j = d_quote_arg(whole_cmd, copy, i, 0);
			if (j == -1)
				return (-1);
		}
		while (whole_cmd[copy->i] == '\'')
		{
			if ((s_quote_arg(whole_cmd, copy, i)) == -1)
				return (-1);
		}
	}
	if (whole_cmd[copy->i] == '\\' && copy->i == (int)ft_strlen(whole_cmd)
		- 1 && whole_cmd[copy->i - 1] != '\\')
		return (j);
	if (whole_cmd[copy->i] == '\\')
		copy->i++;
	return (j);
}

int	args_redir_env(char *whole_cmd, t_copy *copy, int j, size_t i, t_redir *redir)
{
	if (whole_cmd[copy->i] && whole_cmd[copy->i] == '$'
		&& whole_cmd[copy->i - 1] != '\\')
	{
		if (whole_cmd[copy->i + 1] == '\\')
			copy->args[i][++copy->j] = whole_cmd[copy->i];
		else
			j = environnement(whole_cmd, copy, 1, i);
	}
	if ((whole_cmd[copy->i] == '>' || whole_cmd[copy->i] == '<')
		&& whole_cmd[copy->i - 1] != '\\')
		j = redirection(whole_cmd, copy, redir);
	return (j);
}

void	copy_arg(char *whole_cmd, t_copy *copy, size_t i, int j)
{
	if (whole_cmd[copy->i] && (whole_cmd[copy->i] != ' ' || (whole_cmd
				[copy->i] == ' ' && whole_cmd[copy->i - 1] == '\\'))
		&& j != 1 && j != 4 && ((whole_cmd[copy->i] == '$'
				&& whole_cmd[copy->i - 1] == '\\')
			|| (whole_cmd[copy->i] != '$')))
		copy->args[i][++copy->j] = whole_cmd[copy->i];
}

char	*args(char *whole_cmd, t_copy *copy, size_t i, t_redir *redir)
{
	int		j;

	if (init_malloc_args(whole_cmd, copy, i) == -1)
		return (NULL);
	while (whole_cmd[copy->i] && (whole_cmd[++copy->i] != ' '
			|| (whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] == '\\')))
	{
		j = 0;
		j = args_quoting(whole_cmd, copy, j, i);
		j = args_redir_env(whole_cmd, copy, j, i, redir);
		if (j == -3)
			return (copy->args[i]);
		if ((whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] != '\\')
			&& (copy->args[i][0] || (!copy->args[i][0] && (whole_cmd
						[copy->i - 1] == '"' || whole_cmd[copy->i - 1] == '\'')
					&& (whole_cmd[copy->i - 2] == '"' || whole_cmd
						[copy->i - 2] == '\'' || j == 1))))
			break ;
		copy_arg(whole_cmd, copy, i, j);
	}
	copy->args[i][copy->j + 1] = 0;
	return (copy->args[i]);
}
