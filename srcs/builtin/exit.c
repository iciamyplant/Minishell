#include "../../includes/minishell.h"
int pbm;

long long	ft_atoi_minishell(const char *str)
{
    //printf("ca rentre ok\n");
	int		i;
	long	neg;
	long long	sum;

	i = 0;
	neg = 1;
	sum = 0;
    //if (ft_strlen(str) > 19)
    //    error = 1;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
	|| str[i] == '\r' || str[i] == '\v' || str[i] == ' ' || str[i] == '0')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - 48);
        //printf("sum = %lld\n", sum);
        //printf("i = %d et str[i] = %c\n", i, str[i]);
        if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9')) || ((i == 19 && neg == -1) && (str[i] == '9')))
            pbm = 1;
		i++;
	}
    while (str[i])
        i++;
    //if (i > 18 && neg == 1)
    //printf("i = %d\n", i);
	return (sum * neg);
}

int        exit_arg(char *arg)
{
    int i = 0;

    if (arg[i] == '-' || arg[i] == '+')
            i++;
    while (arg[i])
    {
        if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r' && arg[i] != '\v' && arg[i] != ' ')
        {
            if (arg[i] < 48 || arg[i] > 57)
            {
                ft_putstr_fd("minishell: exit: ", 2);
                ft_putstr_fd(arg, 2);
                ft_putstr_fd(": numeric argument required\n", 2);
                code = 255;
                return (-1);
            }
        }
        i++;
    }
    return (1);
}

void		run_exit(char **args)
{
    size_t	i;
    long long code2;
    
    pbm = 0;
    i = 1;
    if (!args[1])
    {
        code = 0;
        exit(code);
    }
    if (args[1] && exit_arg(args[1]) == -1)
            exit(code);
    while (args[i])
        i++;
    //ft_putstr_fd("exit\n", 2);
    if (i > 2)
    {
        ft_putstr_fd("minishell: exit: too many arguments\n", 2);
        code = 1;
    }
    else
    {
        code2 = ft_atoi_minishell(args[1]);
        //printf("code2 = %lld\n", code2);
        if (pbm == 1)
        {
            ft_putstr_fd("minishell: exit: ", 2);
            ft_putstr_fd(args[1], 2);
            ft_putstr_fd(": numeric argument required\n", 2);
            code = 255;
            exit(code);
        }
        code = code2 % 256;
    }
    exit(code);
}