#include "../../includes/minishell.h"

char	*args(char *whole_cmd, t_copy *copy, size_t i, t_redir *redir)
{
	int		j;

	copy->args[i] = NULL;
	copy->j = -1;
	g_error = 0;
	if (!(whole_cmd))
		return (NULL);
	if (!(copy->args[i] = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	while (whole_cmd[copy->i] && whole_cmd[copy->i] == ' ')
		copy->i++;
	copy->i--;
	copy->args[i][0] = 0;
	while (whole_cmd[copy->i] && (whole_cmd[++copy->i] != ' ' || (whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] == '\\')))
	{
		j = 0;
		if ((whole_cmd[copy->i] == '1' || whole_cmd[copy->i] == '2') && whole_cmd[copy->i + 1] == '>' && whole_cmd[copy->i - 1] == ' ')
			copy->i++;
		while (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
		{
			while (whole_cmd[copy->i] == '"')
				if ((j = double_quote_arg(whole_cmd, copy, i)) == -1)
					return (NULL);
			while (whole_cmd[copy->i] == '\'')
				if ((simple_quote_arg(whole_cmd, copy, i)) == -1)
					return (NULL);
		}
		if (whole_cmd[copy->i] == '\\')
			copy->i++;
		if (whole_cmd[copy->i] && whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
		{
			if (whole_cmd[copy->i + 1] == '\\')
				copy->args[i][++copy->j] = whole_cmd[copy->i];
			else
				j = environnement(whole_cmd, copy, 1, i);
		}
		if ((whole_cmd[copy->i] == '>' || whole_cmd[copy->i] == '<') && whole_cmd[copy->i - 1] != '\\')
		{
			j = redirection(whole_cmd, copy, redir);
			if (j == -1)
				return (NULL);
			if (j == -3)
				return (copy->args[i]);
		}
		if ((whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] != '\\') && (copy->args[i][0] || (!copy->args[i][0] 
			&& (whole_cmd[copy->i - 1] == '"' || whole_cmd[copy->i - 1] == '\'') 
			&& (whole_cmd[copy->i - 2] == '"' || whole_cmd[copy->i - 2] == '\'' || j == 1))))
				break;
		if (whole_cmd[copy->i] && (whole_cmd[copy->i] != ' ' || (whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] == '\\')) && j != 1 && j!= 4 && ((whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] == '\\') || (whole_cmd[copy->i] != '$')))
			copy->args[i][++copy->j] = whole_cmd[copy->i];	
	}
	copy->args[i][copy->j + 1] = 0;
	return (copy->args[i]);
}

int		options_special_case(char *arg, char *whole_cmd, t_copy *copy)
{
	int		i;

	i = copy->i - 1;
	if (!arg[0] && (whole_cmd[copy->i - 1] == '"' || whole_cmd[copy->i - 1] == '\'') && 
			(whole_cmd[copy->i - 2] == '"' || whole_cmd[copy->i - 2] == '\'') && !whole_cmd[copy->i])
	{
		while (whole_cmd[i] == '"' || whole_cmd[i] == '\'')
		{
			if (whole_cmd[i - 1] != whole_cmd[i])
				return (0);
			i = i - 2;
		}
		if (whole_cmd[i] != ' ')
			return (0);
		return (1);
	}
	return (0);
}

int		options(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	char	**tmp;
	char	*arg;
	size_t	i;
	size_t	j;

	copy->args = (char **)malloc(sizeof(char *) * 1);
	if (!(copy->args))
		return (-1); 
	copy->args[0] = ft_strdup(copy->cmd);
	i = 1;
	while (1)
	{
		tmp = copy->args;
		if (!(copy->args = (char **)malloc(sizeof(char *) * (i + 2))))
			return (-1);
		j = i;
		while (j)
		{
			copy->args[j - 1] = ft_strdup(tmp[j - 1]);
			j--;
		}
		arg = args(whole_cmd, copy, i, redir);
		if (g_error == -1)
			return (-1);
		//printf("whole_cmd[copy->i] = %c et copy->i = %d\n", whole_cmd[copy->i], copy->i);
		//if (!arg[0] && (whole_cmd[copy->i - 1] == '"' || whole_cmd[copy->i - 1] == '\'') && 
		//	((whole_cmd[copy->i - 2] == '"' || whole_cmd[copy->i - 2] == '\'') && whole_cmd[copy->i - 3] == ' ') && !whole_cmd[copy->i])
		if (options_special_case(arg, whole_cmd, copy) == 1)
			arg = args(whole_cmd, copy, ++i, redir);
		if ((!arg) || (!arg[0] && !whole_cmd[copy->i]))
			break;
		i++;
	}
	copy->args[i] = NULL;
	return (1);
}

void	init_redir_copy(t_copy *copy, t_redir *redir)
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
}

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

char	*cmd(char *whole_cmd, t_copy *copy, t_redir *redir)
{
	int		j;
	init_redir_copy(copy, redir);
	if (!(whole_cmd))
		return (NULL);
	if (!(copy->cmd = malloc(sizeof(char) * (strlen(whole_cmd) + 1))))
		return (NULL);
	copy->cmd[0] = 0;
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
	if (options(whole_cmd, copy, redir) == -1)
		return (NULL);
	return (copy->cmd);
}