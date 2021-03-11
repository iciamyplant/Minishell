#include "../../includes/minishell.h"

static size_t	_check_n(char **args)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (args[i][j++] == '-')
		{
			while (args[i][j] == 'n')
				j++;
			if (args[i][j] && args[i][j] != 'n')
				return (i + 1);
		}
		else
			return (i);
	}
	return (i);
}

int	run_echo(char **args)
{
	size_t	i;
	int		n;
	
	n = 1;
	g_status = 0;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	if ((ft_strequ(args[1], " ") && !args[2]))
		return (1);
	if ((i = _check_n(args)) > 1)
		n = 0;
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		i++;
		if (args[i])
			ft_putchar_fd(' ', 1);
	}
	if (n)
		ft_putchar_fd('\n', 1);
	return (1);
}