#include "../includes/minishell.h"

void	ft_exit()
{
	exit(g_status);
}

static int	_check_space_colon(char *line)
{
	size_t	i;
	int		colon;

	colon = 0;
	i = 0;
	while (line[i])
	{
		if ((line[i] == ':' && colon) || (!ft_isspace(line[i]) && line[i] != ':'))
			return (0);
		if (line[i] == ':')
			colon = 1;
		i++;
	}
	prompt();
	return (1);
}

void	loop()
{
	t_sep	*list;
	char	*line;
	char	**cmds;
	size_t	i;
	
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigint_handler);

	prompt();
	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (_check_space_colon(line))
			continue;
		list = NULL;
		i = -1;
		if (syntax_error(line, '|') != -1 && syntax_error(line, ';') != -1)
		{
			cmds = ft_minishell_split(line, ';');
			while (cmds[++i])
				list = add_cell(list, cmds[i], i);
			free(line);
			parse_pip(list);
			minishell(list);
		}
		else
		{
			//printf(" g_status= %d\n", g_status);
			free(line);
		}
		prompt();
		
	}
	ft_putstr_fd("exit\n", 1);
	ft_exit();
}

void	loop_testeur(char *line)
{
	t_sep	*list;
	char	**cmds;
	size_t	i;

	if (_check_space_colon(line))
		return;
	list = NULL;
	i = -1;
	if (syntax_error(line, '|') != -1 && syntax_error(line, ';') != -1)
	{
		cmds = ft_minishell_split(line, ';');
		while (cmds[++i])
			list = add_cell(list, cmds[i], i);
		parse_pip(list);
		minishell(list);
	}
	ft_exit();
}

void	prompt()
{
	char	pwd[4096 + 1];
	char	*user;
	size_t	len;
	size_t	count_slash;

	if ((user = get_env("USER")))
	{
		ft_putstr_fd("\033[32;1m", 1);
		ft_putstr_fd(user, 1);
		ft_putstr_fd("@\033[0m:", 1);
		free(user);
	}
	if (!getcwd(pwd, 4096))
	{
		ft_putstr_fd("$ ", 1);
		return;
	}
	len = ft_strlen(pwd);
	count_slash = 0;
	while (--len && count_slash < 3)
		if (pwd[len] == '/')
			count_slash++;
	ft_putstr_fd("\e[1;34m", 1);
	while (pwd[++len])
		ft_putchar_fd(pwd[len], 1);
	ft_putstr_fd("$\e[0m ", 1);
}

int	main(int ac, char **av, char **env)
{
	g_envs = env;
	if (ac >= 2)
	{
		if (av[1][0] == '-' && av[1][1] == 'c')
			loop_testeur(av[2]);
	}
	else
		loop();
	return (0);
}
