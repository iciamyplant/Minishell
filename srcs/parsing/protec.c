#include "../../includes/minishell.h"

int		simple_quote(char *whole_cmd, t_copy *copy)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le ' ouvrant est le dernier caractere de la chaine
	{
			ft_putstr_fd("minishell: unexpected EOF while looking for matching `''\n", 2);
			g_status = 1;
			return (-1);
	}
	if (whole_cmd[copy->i + 1] == '\'' && (whole_cmd[copy->i + 2] == ' ' || whole_cmd[copy->i + 2] == '\0'))
		copy->cmd[++copy->j] = '\0';
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'') //++copy->i; //on decale de 1 car on est sur le ' ouvrant
		copy->cmd[++copy->j] = whole_cmd[copy->i];
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '\'') // si y a pas de ' fermant
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `''\n", 2);
		g_status = 1;
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le ' fermant
	return (-2);
}

int		simple_quote_arg(char *whole_cmd, t_copy *copy, size_t i) //////////segfault
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le ' ouvrant est le dernier caractere de la chaine
	{
		g_error = -1;
		g_status = 1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `''\n", 2);
		return (-1);
	}
	if (whole_cmd[copy->i + 1] == '\'' && (whole_cmd[copy->i + 2] == ' ' || whole_cmd[copy->i + 2] == '\0'))
		copy->args[i][++copy->j] = '\0';
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'') //++copy->i; //on decale de 1 car on est sur le ' ouvrant
		copy->args[i][++copy->j] = whole_cmd[copy->i];
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '\'') // si y a pas de ' fermant
	{
		g_error = -1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `''\n", 2);
		g_status = 1;
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le ' fermant
	return (1);
}

int		simple_quote_redir(char *whole_cmd, t_copy *copy, int i, t_redir *redir, char *str)
{
	if (copy->i == (strlen(whole_cmd) -1)) // si le ' ouvrant est le dernier caractere de la chaine
	{
		g_error = -1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `''\n", 2);
		g_status = 1;
		return (-1);
	}
	if ((whole_cmd[copy->i + 1] == '\'' && whole_cmd[copy->i + 2] == ' ') && !str) // cas de : echo bonjour 1>'' pas normal //et : echo bonjour 1> "hey"'' pas normal
	{
		str[redir->i] = ' ';
		str[redir->i + 1] = 0;
		copy->i = copy->i + 2;
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '\'') //++copy->i; //on decale de 1 car on est sur le ' ouvrant
		str[++redir->i] = whole_cmd[copy->i];
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '\'') // si y a pas de ' fermant
	{
		g_error = -1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `''\n", 2);
		g_status = 1;
		return (-1);
	}
	str[redir->i + 1] = 0;
	copy->i++; // on decale de 1 car on est sur le ' fermant
	if (whole_cmd[copy->i] != ' ')
		return (1);
	return (-1);
}

int		double_quote(char *whole_cmd, t_copy *copy)
{
	int j;
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
		g_status = 1;
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		j = 0;
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
			j = environnement(whole_cmd, copy, 0, 0);
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		if (j != 1)
			copy->cmd[++copy->j] = whole_cmd[copy->i];
	}
	if (whole_cmd[copy->i] == '"' && (whole_cmd[copy->i + 1] == ' ' || whole_cmd[copy->i + 1] == '\0') && !copy->cmd[0])
		copy->cmd[0] = '\0';
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
		g_status = 1;
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le " fermant
	if (copy->cmd[0] == '\0' && (whole_cmd[copy->i] == ' ' || whole_cmd[copy->i] == '\0'))
		return (1);
	return (-2);
}

int		double_quote_arg(char *whole_cmd, t_copy *copy, size_t i)
{
	int j;
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		g_error = -1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
		g_status = 1;
		return (-1);
	}
	while (whole_cmd[copy->i] && whole_cmd[++copy->i] != '"') //++copy->i; //on decale de 1 car on est sur le " ouvrant
	{
		j = 0;
		if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\') // $ conserve sa signification speciale
		{
			j = environnement(whole_cmd, copy, 1, i);
			if (j == -2)
			{
				copy->i--;
				j = 1;
			}
			//printf("ca rentre pour %c, à copy->i = %d et j = %d\n", whole_cmd[copy->i], copy->i, j);
		}
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		if (j != 1)
		{
			copy->args[i][++copy->j] = whole_cmd[copy->i];
			//printf("ca rentre pour %c, à copy->i = %d et j = %d\n", whole_cmd[copy->i], copy->i, j);
		}
	}
	if (whole_cmd[copy->i] == '"' && (whole_cmd[copy->i + 1] == ' ' || whole_cmd[copy->i + 1] == '\0') && !copy->args[i][0])
	{
		//printf("ca rentre mdrrrr\n");
		copy->args[i][0] = '\0';
	}
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
	{
		g_error = -1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
		g_status = 1;
		return (-1);
	}
	copy->i++; // on decale de 1 car on est sur le " fermant
	//printf("whole_cmd[copy->i] = %c\n", whole_cmd[copy->i]);
	if (copy->args[i][0] == '\0' && (whole_cmd[copy->i] == ' ' || whole_cmd[copy->i] == '\0'))
		return (1);
	return (0);
}

int		double_quote_redir(char *whole_cmd, t_copy *copy, t_redir *redir, char *str, int std)
{
	int j;
	if (copy->i == (strlen(whole_cmd) -1)) // si le " ouvrant est le dernier caractere de la chaine
	{
		g_error = -1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
		g_status = 1;
		return (-1);
	}
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
			//printf("ca rentre ici a whole_cmd[%d] = %c\n", copy->i, whole_cmd[copy->i]);
			j = environnement_redir(whole_cmd, copy, std, redir);
			if (j == -2)
			{
				copy->i--;
				j = 1;
			}
			if (whole_cmd[copy->i] == '"' && whole_cmd[copy->i - 1] != '\\') // cas de : echo bonjour 1> "$PATHH"
			{
				//printf("ca rentre 2\n");
				break;				
			}
			//printf("ca rentre ici a whole_cmd[%d] = %c\n", copy->i, whole_cmd[copy->i]);
		}
		if (whole_cmd[copy->i] == '\\')
		{
			if (whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i + 1] == '\\' // si \ suivit de " $ ou \ garde sa signification
					|| whole_cmd[copy->i + 1] == '"')
				copy->i++;
		}
		if (j != 1)
			str[++redir->i] = whole_cmd[copy->i];
		//printf("str[%d] = %c, whole_cmd[%d] = %c\n", redir->i, str[redir->i], copy->i, whole_cmd[copy->i]);
	}
	if ((copy->i == strlen(whole_cmd)) && whole_cmd[copy->i] != '"') // si y a pas de " fermant
	{
		g_error = -1;
		ft_putstr_fd("minishell: unexpected EOF while looking for matching \"\n", 2);
		g_status = 1;
		return (-1);
	}
	str[redir->i + 1] = 0;
	copy->i++; // on decale de 1 car on est sur le " fermant
	if (whole_cmd[copy->i] != ' ')
		return (1);
	return (-1);
}