#include "../../includes/minishell.h"
int pbm;

long long	ft_atoi_exit(const char *str)
{
	int		i;
	long	neg;
	long long	sum;

	i = 0;
	neg = 1;
	sum = 0;
    int j = 0;
    if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == ' ' || str[i] == '0')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - 48);
        if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9')) || ((i == 19 && neg == -1) && (str[i] == '9')))
            pbm = 1;
		i++;
        j++;
	}
    while (str[i++])
        j++;
    if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
        pbm = 1;
	return (sum * neg);
}

void        exit_error_numeric(char *arg)
{
    ft_putstr_fd("minishell: ligne 0 : exit: ", 2);
    ft_putstr_fd(arg, 2);
    ft_putstr_fd(" : argument numérique nécessaire\n", 2);
    g_status = 2;
    exit(g_status);
}

void        exit_arg(char *arg)
{
    int i = 0;

    if (arg[i] == '-' || arg[i] == '+')
            i++;
    while (arg[i])
    {
        if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r' && arg[i] != '\v' && arg[i] != ' ')
        {
            if (arg[i] < 48 || arg[i] > 57)
                exit_error_numeric(arg);
        }
        i++;
    }
}

void		run_exit(char **args)
{
    size_t	i;
    long long code2;
    
    pbm = 0;
    i = 1;
    g_status = 0;
    if (!args[1])
        exit(g_status);
    exit_arg(args[1]);
    while (args[i])
        i++;
    if (i > 2)
    {
        ft_putstr_fd("minishell: ligne 0 : exit: trop d'arguments\n", 2);
        g_status = 1;
    }
    else
    {
        code2 = ft_atoi_exit(args[1]);
        if (pbm == 1)
            exit_error_numeric(args[1]);
        g_status = code2 % 256;
    }
    exit (g_status);
}
