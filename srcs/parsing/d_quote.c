#include "../../includes/minishell.h"

int	d_quote(char *whole_cmd, t_copy *copy, int j)
{
	if (copy->i == (ft_strlen(whole_cmd) - 1))
		return (quote_error('"'));
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"')
	{
		j = 0;
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
			j = environnement(whole_cmd, copy, 0, 0);
		if (whole_cmd[copy->i] == '\\')
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\'
				|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		if (j != 1)
			copy->cmd[++copy->j] = whole_cmd[copy->i];
	}
	if (whole_cmd[copy->i] == '"' && (whole_cmd[copy->i + 1] == ' '
			|| whole_cmd[copy->i + 1] == '\0') && !copy->cmd[0])
		copy->cmd[0] = '\0';
	if ((copy->i == ft_strlen(whole_cmd)) && whole_cmd[copy->i] != '"')
		return (quote_error('"'));
	copy->i++;
	if (copy->cmd[0] == '\0' && (whole_cmd[copy->i] == ' '
			|| whole_cmd[copy->i] == '\0'))
		return (1);
	return (-2);
}

int	d_quote_arg_util(char *whole_cmd, t_copy *copy, int j, size_t i)
{
	if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
	{
		j = environnement(whole_cmd, copy, 1, i);
		if (j == -2)
		{
			copy->i--;
			j = 1;
		}
	}
	if (whole_cmd[copy->i] == '\\')
	{
		if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\'
			|| whole_cmd[copy->i + 1] == '"')
			copy->i++;
	}
	return (j);
}

int	d_quote_arg(char *whole_cmd, t_copy *copy, size_t i, int j)
{
	if (copy->i == (ft_strlen(whole_cmd) - 1))
		return (quote_error('"'));
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"')
	{
		j = 0;
		j = d_quote_arg_util(whole_cmd, copy, j, i);
		if (j != 1)
			copy->args[i][++copy->j] = whole_cmd[copy->i];
	}
	if (whole_cmd[copy->i] == '"' && (whole_cmd[copy->i + 1] == ' '
			|| whole_cmd[copy->i + 1] == '\0') && !copy->args[i][0])
		copy->args[i][0] = '\0';
	if ((copy->i == ft_strlen(whole_cmd)) && whole_cmd[copy->i] != '"')
		return (quote_error('"'));
	copy->i++;
	if (copy->args[i][0] == '\0' && (whole_cmd[copy->i] == ' '
			|| whole_cmd[copy->i] == '\0'))
		return (1);
	return (0);
}

int	d_quote_redir(char *whole_cmd, t_copy *copy, t_redir *redir, char *str, int std)
{
	int j;
	if (copy->i == (strlen(whole_cmd) - 1)) // si le " ouvrant est le dernier caractere de la chaine
		return (quote_error('"'));
	if ((whole_cmd[copy->i + 1] == '"' && whole_cmd[copy->i + 2] == ' ') && !str) // cas de : echo bonjour 1>"" pas normal ou de : echo bonjour 1> "hey""" pas normal
	{
		str[redir->i] = ' ';
		str[redir->i + 1] = 0;
		copy->i = copy->i + 2;
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		j = 0;
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
		{
			j = environnement_redir(whole_cmd, copy, std, redir);
			if (j == -2)
			{
				copy->i--;
				j = 1;
			}
			if (whole_cmd[copy->i] == '"' && whole_cmd[copy->i - 1] != '\\') // cas de : echo bonjour 1> "$PATHH"
				break;				
		}
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		if (j != 1)
			str[++redir->i] = whole_cmd[copy->i];
	}
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
		return (quote_error('"'));
	str[redir->i + 1] = 0;
	copy->i++; // on decale de 1 car on est sur le " fermant
	if (whole_cmd[copy->i] != ' ')
		return (1);
	return (-1);
}