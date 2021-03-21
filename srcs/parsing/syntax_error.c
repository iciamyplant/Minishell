/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 03:33:35 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 03:33:51 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	inside_quote(char *str, int i)
{
	char	quote;

	while (str[i] && (str[i] == '\'' || str[i] == '"'))
	{
		quote = str[i];
		i++;
		while (str[i] && str[i] != quote)
		{
			if (str[i] && str[i] == '\\')
				i++;
			i++;
		}
		if (i == ((int)ft_strlen(str)))
			break ;
		else
			i++;
	}
	return (i);
}

int	syntax_error_redir(char *str, char c)
{
	int		i;
	int		j;

	i = 0;
	while (str[i])
	{
		j = 0;
		if ((i = (inside_quote(str, i))) == (int)ft_strlen(str))
			break ;
		while (str[i] && (str[i] == c || str[i] == ' '))
		{
			if (str[i] == c)
				j++;
			i++;
			if (j == 3)
				return (error_msg(str, i + 1, c));
			if (j > 3)
				return (error_msg(str, i, c));
		}
		if (i == (int)ft_strlen(str))
			break ;
		i++;
	}
	return (0);
}

int	syntax_error_newline(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	i--;
	if (str[i] == '>' || str[i] == '<')
		return (error_msg(str, i, 'n'));
	i++;
	while (str[i--] && (str[i] == ' ' || str[i] == '<' || str[i] == '>'))
	{
		if ((i = (inside_quote(str, i))) == (int)ft_strlen(str))
			break ;
		if (str[i] == '>' || str[i] == '<')
			return (error_msg(str, i, 'n'));
	}
	return (0);
}

int	syntax_error_go(char *str, int i, char c)
{
	i--;
	if (str[i] && str[i] == '|')
		return (error_msg(str, i, c));
	if (syntax_error_redir(str, '>') == -1 || syntax_error_redir(str, '<') == -1
		|| syntax_error_newline(str) == -1)
	{
		g_status = 2;
		return (-1);
	}
	return (0);
}

int	syntax_error(char *str, char c, int i)
{
	if (!str)
		return (0);
	if (str[0] == c)
		return (error_msg(str, 0, c));
	while (str[++i] && (str[i] == ' ' || str[i] == '>'
			|| str[i] == '<' || str[i] == c))
		if (str[i] == c)
			return (error_msg(str, i, c));
	while (str[i])
	{
		if ((i = (inside_quote(str, i))) == (int)ft_strlen(str))
			break ;
		if (str[i] && str[i] == c)
		{
			while (str[++i] && (str[i] == ' ' || str[i] == '>'
					|| str[i] == '<' || str[i] == c))
				if (str[i] == c)
					return (error_msg(str, i, c));
			if (str[i] == '\0')
				break ;
		}
		i++;
	}
	return (syntax_error_go(str, i, c));
}
