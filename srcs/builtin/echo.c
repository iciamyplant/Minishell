#include "../../includes/minishell.h"

int	run_echo(char **args)
{
	size_t	i;
	int		n;

	n = 0;
	i = 1;
	
	code = 0;
	if (!args[1])
	{
		ft_putchar_fd('\n', 1);
		return (1);
	}
	if ((ft_strequ(args[1], " ") && !args[2]))
		return (1);
	while (args[i] && ft_strequ(args[i], "-n"))
	{
		n++;
		i++;
	}
	while (args[i])
	{
		if ((i > 1 && !n) || (i > n + 1 && n))
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(args[i], 1);
		i++;
	}
	if (!n)
		ft_putchar_fd('\n', 1);
	return (1);
}
