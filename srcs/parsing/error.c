#include "../../includes/minishell.h"

int		ft_error_token(char *msg, char c, int i, char *str)
{
	char s1[5] = {c, c, '\'', '\n', '\0'};
	char s2[4] = {c, '\'', '\n', '\0'};
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(msg, 2);
	if (c == 'n')
		ft_putstr_fd("newline'\n", 2);
	else if (str[i - 1] == c || str[i + 1] == c)
		ft_putstr_fd(s1, 2);
	else
		ft_putstr_fd(s2, 2);
	code = 258;
	return (-1);
}

int		syntax_error_redir(char *str, char c)
{
	int i;
	int j = -1;
	char quote;

	i = -1;
	while (str[++i])
	{
		j = 0;
		while (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
            while (str[i] && str[++i] != quote)
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		while (str[i] == c || str[i] == ' ')
		{
			if (str[i] == c)
				j++;
			i++;
			if (j == 3)
			{
				ft_error_token("syntax error near unexpected token `", c, i + 1, str);
				code = 258;
				return (-1);
			}
			if (j > 3)
			{
				ft_error_token("syntax error near unexpected token `", c, i, str);
				code = 258;
				return (-1);
			}
		}
	}
	return (0);
}

int		syntax_error_newline(char *str)
{
	int i;
	char quote;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '>' || str[i] == '<')
	{
		ft_error_token("syntax error near unexpected token `", 'n', i, str);
		code = 258;
		return (-1);
	}
	i++;
	while (str[i--] && (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
	{
		while (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
            while (str[i] && str[++i] != quote)
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		if (str[i] == '>' || str[i] == '<')
		{
			ft_error_token("syntax error near unexpected token `", 'n', i, str);
			code = 258;
			return (-1);
		}
	}
	return (0);
}

int		syntax_error(char *str, char c)
{
	int i;
	char quote;

	i = -1;
	if (str[0] == c)
	{
		ft_error_token("syntax error near unexpected token `", c, 0, str);
		code = 258;
		return (-1);
	}
	while (str[++i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<' || str[i] == c))
		if (str[i] == c)
		{
			ft_error_token("syntax error near unexpected token `", c, i, str);
			code = 258;
			return (-1);
		}
	while (str[++i])
	{
		while (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i];
            while (str[i] && str[++i] != quote)
			{
				if (str[i] == '\\')
					i++;
			}
			i++;
		}
		if (str[i] == c)
		{
			while (str[++i] && (str[i] == ' ' || str[i] == '>' || str[i] == '<' || str[i] == c))
				if (str[i] == c)
				{
					ft_error_token("syntax error near unexpected token `", c, i, str);
					code = 258;
					return (-1);
				}
			if (str[i] == '\0')
				break;
		}
	}
	i--;
	if (str[i] == '|')
	{
		ft_error_token("syntax error near unexpected token `", c, i, str);
		code = 258;
		return (-1);
	}
	if (syntax_error_redir(str, '>') == -1 || syntax_error_redir(str, '<') == -1 || syntax_error_newline(str) == -1)
	{
		code = 258;
		return (-1);
	}
	return (0);
}

void	ft_error_exit(char *str, char *msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	if (errno != 0)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	error = -1;
	code = 1;
}