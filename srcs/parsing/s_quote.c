#include "../../includes/minishell.h"

int	quote_error(char c)
{
	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_status = 1;
	g_error = -1;
	return (-1);
}

int	s_quote(char *whole_cmd, t_copy *copy)
{
	if (copy->i == (ft_strlen(whole_cmd) - 1))
		return (quote_error('\''));
	if (whole_cmd[copy->i + 1] == '\'' && (whole_cmd[copy->i + 2] == ' '
			|| whole_cmd[copy->i + 2] == '\0'))
		copy->cmd[++copy->j] = '\0';
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'')
		copy->cmd[++copy->j] = whole_cmd[copy->i];
	if ((copy->i == ft_strlen(whole_cmd)) && whole_cmd[copy->i] != '\'')
		return (quote_error('\''));
	copy->i++;
	return (-2);
}

int	s_quote_arg(char *whole_cmd, t_copy *copy, size_t i)
{
	if (copy->i == (ft_strlen(whole_cmd) - 1))
		return (quote_error('\''));
	if (whole_cmd[copy->i + 1] == '\'' && (whole_cmd[copy->i + 2] == ' '
			|| whole_cmd[copy->i + 2] == '\0'))
		copy->args[i][++copy->j] = '\0';
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'')
		copy->args[i][++copy->j] = whole_cmd[copy->i];
	if ((copy->i == ft_strlen(whole_cmd)) && whole_cmd[copy->i] != '\'')
		return (quote_error('\''));
	copy->i++;
	return (1);
}

int	s_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str)
{
	if (copy->i == (ft_strlen(whole_cmd) - 1))
		return (quote_error('\''));
	if ((whole_cmd[copy->i + 1] == '\'' && whole_cmd[copy->i + 2] == ' ')
		&& !str)
	// echo bonjour 1>'' pas normal //et : echo bonjour 1> "hey"'' pas normal
	{
		str[redir->i] = ' ';
		str[redir->i + 1] = 0;
		copy->i = copy->i + 2;
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'')
		str[++redir->i] = whole_cmd[copy->i];
	if ((copy->i == ft_strlen(whole_cmd)) && whole_cmd[copy->i] != '\'')
		return (quote_error('\''));
	str[redir->i + 1] = 0;
	copy->i++;
	if (whole_cmd[copy->i] != ' ')
		return (1);
	return (-1);
}
