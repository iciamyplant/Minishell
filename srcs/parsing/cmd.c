#include "../../includes/minishell.h"

int	cmd_quoting(char *whole_cmd, t_copy *copy, int j)
{
	while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
	{
		while (whole_cmd[copy->i] == '"')
		{
			j = d_quote(whole_cmd, copy, j);
			if (j == -1)
				return (-1);
		}
		while (whole_cmd[copy->i] == '\'')
		{
			j = s_quote(whole_cmd, copy);
			if (j == -1)
				return (-1);
		}
	}
	if (whole_cmd[copy->i] == '\\')
		copy->i++;
	return (j);
}

int	cmd_redir_env(char *whole_cmd, t_copy *copy, int j, t_redir *redir)
{
	if (whole_cmd[copy->i] && whole_cmd[copy->i] == '$'
		&& whole_cmd[copy->i - 1] != '\\')
	{
		if (whole_cmd[copy->i + 1] == '\\')
			copy->cmd[++copy->j] = whole_cmd[copy->i];
		else
			j = environnement(whole_cmd, copy, 0, 0);
	}
	if ((whole_cmd[copy->i] == '>' || whole_cmd[copy->i] == '<')
		&& whole_cmd[copy->i - 1] != '\\')
		j = redirection(whole_cmd, copy, redir);
	return (j);
}

char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	int		j;

	while (whole_cmd[copy->i] && whole_cmd[copy->i] != ' ')
	{
		j = -2;
		if ((whole_cmd[copy->i] == '1' || whole_cmd[copy->i] == '2')
			&& whole_cmd[copy->i + 1] == '>'
			&& (!copy->cmd[0] || whole_cmd[copy->i - 1] == ' '))
			copy->i++;
		j = cmd_quoting(whole_cmd, copy, j);
		j = cmd_redir_env(whole_cmd, copy, j, redir);
		if ((whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] != '\\')
			&& (copy->cmd[0] || (!copy->cmd[0] && (whole_cmd[copy->i - 1] == '"'
						|| whole_cmd[copy->i - 1] == '\'') && (whole_cmd
						[copy->i - 2] == '"' || whole_cmd[copy->i - 2] == '\''
						|| j == 1))))
			break ;
		if (copy->i < (int)ft_strlen(whole_cmd) && ((whole_cmd[copy->i] == '$'
					&& whole_cmd[copy->i - 1] == '\\') || (whole_cmd[copy->i]
					!= '$' && j == -2)))
			copy->cmd[++copy->j] = whole_cmd[copy->i];
		copy->i++;
	}
	copy->cmd[copy->j + 1] = 0;
	return (copy->cmd);
}

char	*parsing(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	copy->i = 0;
	copy->j = -1;
	copy->cmd = NULL;
	redir->sstdout = 1;
	redir->sstderr = 2;
	redir->sstdin = 1;
	redir->out1 = NULL;
	redir->out2 = NULL;
	redir->in = NULL;
	g_error = 0;
	copy->cmd = malloc(sizeof(char) * (strlen(whole_cmd) + 1));
	if (!(copy->cmd) || !(whole_cmd))
		return (NULL);
	copy->cmd[0] = 0;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	if (cmd(whole_cmd, copy, redir) == NULL || g_error == -1)
		return (NULL);
	copy->args = (char **)malloc(sizeof(char *) * 1);
	if (!(copy->args) || options(whole_cmd, copy, redir, 1, 0) == -1)
		return (NULL);
	return (copy->cmd);
}

/*char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	int		j;

	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	while (whole_cmd[copy->i] && whole_cmd[copy->i] != ' ')
	{
		j = -2;
		if ((whole_cmd[copy->i] == '1' || whole_cmd[copy->i] == '2') && whole_cmd[copy->i + 1] == '>' && (!copy->cmd[0] || whole_cmd[copy->i - 1] == ' '))
			copy->i++;
		while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
		{
			while (whole_cmd[copy->i] == '"')
				if ((j = double_quote(whole_cmd, copy)) == -1)
					return (NULL);
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote(whole_cmd, copy)) == -1)
					return (NULL);
		}
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
		j = quoting(whole_cmd, copy);
		if (j == -1)
			return (NULL);
		if (whole_cmd[copy->i] && whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
		{
			if (whole_cmd[copy->i + 1] == '\\')
				copy->cmd[++copy->j] = whole_cmd[copy->i];
			else
				j = environnement(whole_cmd, copy, 0, 0);
		}
		if ((whole_cmd[copy->i] == '>' || whole_cmd[copy->i] == '<') && whole_cmd[copy->i - 1] != '\\')
		{
			j = redirection(whole_cmd, copy, redir);
			if (j == -1)
				return (NULL);
		}
		if ((whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] != '\\') && (copy->cmd[0] || (!copy->cmd[0] 
			&& (whole_cmd[copy->i - 1] == '"' || whole_cmd[copy->i - 1] == '\'') 
			&& (whole_cmd[copy->i - 2] == '"' || whole_cmd[copy->i - 2] == '\'' || j == 1))))
				break;
		if (copy->i < strlen(whole_cmd) && ((whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] == '\\') || (whole_cmd[copy->i] != '$' && j == -2)))
			copy->cmd[++copy->j] = whole_cmd[copy->i];
		copy->i++;
	}
	copy->cmd[copy->j + 1] = 0;
	return (copy->cmd);
}*/

void	print_parsing(char **args, t_redir *redir)
{
	int i = 0;
	int j = 0;

	while (args[i])
	{
		printf("arg[%d] = %s\n", i, args[i]);
		i++;
	}
	if (redir->in)
	{
		printf("file stdin = %s\n", redir->in);
		printf("fd stdin = %d\n", redir->sstdin);
	}
	if (redir->out1)
	{
		printf("file stdout = %s\n", redir->out1);
		printf("fd stdout = %d\n", redir->sstdout);
		printf("fin du fichier ? = %d\n", redir->end);
	}
	if (redir->out2)
	{
		printf("file stderr = %s\n", redir->out2);
		printf("fd stderr = %d\n", redir->sstderr);
		printf("fin du fichier ? = %d\n", redir->end);
	}
	printf("g_status = %d\n", g_status);
}
