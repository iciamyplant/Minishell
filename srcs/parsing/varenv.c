#include "../../includes/minishell.h"

char    *remalloc_cmdargs(t_copy *copy, char *value, char *whole_cmd, char *str) // remalloc str et ajouter value à sa valeur initiale
{
    char *tmp;
    int j = -1;
    
    tmp = NULL;
    str[copy->j + 1] = 0;
    tmp = ft_strjoin(str, value);
    copy->j = -1;
    if (!(str = malloc(sizeof(char) * (strlen(tmp) + strlen(whole_cmd) + 1))))
        return (NULL);
    while (tmp[++j])
        str[++copy->j] = tmp[j];
    return (str);
}

int	    environnement(char *whole_cmd, t_copy *copy, int arg, int i, int space) //variable d'environnement dans un argument ou dans la commande
{
	char *name;
    int  quote;
    char *value;
    int j;
    int count = -1;

    value = NULL;
    quote = 0;
    name = NULL;
    if (!(name = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
    j = 0;
    if (whole_cmd[copy->i - 1] == '"' || whole_cmd[copy->i - 1] == '\'') // cas de $PA\TH ou faut pas mettre le backslash
        quote = 1;
    while (whole_cmd[copy->i] && whole_cmd[copy->i] == '$' && (whole_cmd[copy->i + 1] == '\0' || whole_cmd[copy->i + 1] == '$' || whole_cmd[copy->i - 1] == '$'))
    {
        if (arg == 0) // pour le cas de : echo "$PAT\H"
                copy->cmd[++copy->j] = whole_cmd[copy->i];
        if (arg == 1)
            copy->args[i][++copy->j] = whole_cmd[copy->i];
        copy->i++;
        j++;
    }
    if (j > 0) //pour le cas precedent de echo $COLORTERM$$hey ou echo $$$$
    {
        copy->i--;
        return (1);
    }
    if (whole_cmd[copy->i] && whole_cmd[copy->i - 1] != '\\' && whole_cmd[copy->i - 1] != '$' && whole_cmd[copy->i] == '$' && whole_cmd[copy->i + 1] == '?')
    {
        //printf("%d\n", g_status);
        value = ft_itoa(g_status);
        if (arg == 0) // si arg = 0 faut changer copy->cmd
            copy->cmd = remalloc_cmdargs(copy, value, whole_cmd, copy->cmd);
        else if (arg == 1)// si arg = 1 faut changer copy->args[i]
            copy->args[i] = remalloc_cmdargs(copy, value, whole_cmd, copy->args[i]);
        copy->i++;
        return (1);
    }
    copy->i++;
    //printf("ca rentre a whole_cmd[%d] = %c\n", copy->i, whole_cmd[copy->i]);
    if (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
    {
        copy->i--;
        return (0);
    }
    while (whole_cmd[copy->i] && (whole_cmd[copy->i] != '\\' && whole_cmd[copy->i] != ' ' && whole_cmd[copy->i] != '$' 
        && whole_cmd[copy->i] != '"' && whole_cmd[copy->i] != '\'' && whole_cmd[copy->i] != '/' && whole_cmd[copy->i] != '=' && whole_cmd[copy->i] != '|' && whole_cmd[copy->i] != '@'))
    {
        if (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
            return (0);
        name[++count] = whole_cmd[copy->i];
        copy->i++;
    }
    name[count + 1] = 0;
    //printf("name = %s\n", name);
    value = get_env(name);
    if (space == 1 && value) // on est pas dans une double quote, donc faut enlever les espaces etc
        value = ft_strip_extra_spaces(value, whole_cmd, copy->i);
    //printf("value = %s\n", value);
    if (!value)
    {
        if (whole_cmd[copy->i] == '"' || whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '\\' || whole_cmd[copy->i] == '|' || whole_cmd[copy->i] == '/' || whole_cmd[copy->i] == '=')
            copy->i--;
        if (whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] != '\\')
            return (-2);
        if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
            copy->i--;
        return (1);
    }
    if (arg == 0) // si arg = 0 faut changer copy->cmd
        copy->cmd = remalloc_cmdargs(copy, value, whole_cmd, copy->cmd);
    else if (arg == 1)// si arg = 1 faut changer copy->args[i]
        copy->args[i] = remalloc_cmdargs(copy, value, whole_cmd, copy->args[i]);
    copy->i--;
    return (1);
}

char    *remalloc_redir(t_copy *copy, char *value, char *whole_cmd, char *str, t_redir *redir) // remalloc str et ajouter value à sa valeur initiale
{
    char *tmp;
    int j = -1;
    
    tmp = NULL;
    str[redir->i + 1] = 0;
    tmp = ft_strjoin(str, value);
    if (!(str = malloc(sizeof(char) * (strlen(tmp) + 1))))
        return (NULL);
    while (tmp[++j])
        str[j] = tmp[j];
    str[j] = 0;
    redir->i = strlen(str);
    return (str);
}

int		environnement_redir(char *whole_cmd, t_copy *copy, int std, t_redir *redir) //variable d'environnement dans un nom de fichier de redirection
{
	char *name;
    char *value;
    int count = -1;

    if (!(name = malloc(sizeof(char) * strlen(whole_cmd) + 1)))
		return (-1);
    copy->i++;
    if (whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '"')
    {
        //copy->i--;
        return (0);
    }  
    while (whole_cmd[copy->i] && (whole_cmd[copy->i] != '\\' && whole_cmd[copy->i] != ' ' && whole_cmd[copy->i] != '$' 
        && whole_cmd[copy->i] != '"' && whole_cmd[copy->i] != '\'' && whole_cmd[copy->i] != '|'))
    {
        name[++count] = whole_cmd[copy->i];
        copy->i++;
    }
    name[count + 1] = 0;
    value = get_env(name);
    if (!value)
    {
        if (whole_cmd[copy->i] == '"' || whole_cmd[copy->i] == '\'' || whole_cmd[copy->i] == '|' || whole_cmd[copy->i] == '\\' || whole_cmd[copy->i] == '/' || whole_cmd[copy->i] == '=')
            copy->i--;
        if (whole_cmd[copy->i] == ' ' && whole_cmd[copy->i - 1] != '\\')
            return (-2);
        if (whole_cmd[copy->i] == '$' && whole_cmd[copy->i - 1] != '\\')
            copy->i--;
        return (1);
    }
    if (std == 0) //redirection de stdin
        redir->in = remalloc_redir(copy, value, whole_cmd, redir->in, redir);
    if (std == 1) //redirection de stdout
        redir->out1 = remalloc_redir(copy, value, whole_cmd, redir->out1, redir);
    if (std == 2) //redirection de stderr
        redir->out2 = remalloc_redir(copy, value, whole_cmd, redir->out2, redir);
    copy->i--;
    return (1);
}