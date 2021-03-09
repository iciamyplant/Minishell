#include "../../../includes/minishell.h"

static char	**_dup_env(void)
{
	char	**dup;
	size_t	count;
	
	count = (get_envs_count());
	if (!(dup = (char **)malloc(sizeof(char *) * (count + 1))))
		return (NULL);
	dup[count] = 0;
	count--;
	while (count != -1)
	{
		dup[count] = ft_strdup(g_envs[count]);
		count--;
	}
	return (dup);
}

static void	_print_export(char **export)
{
	size_t	i;
	size_t	j;
	char	equ;

	i = 0;
	while (export[i])
	{
		equ = 1;
		j = 0;
		ft_putstr_fd("declare -x ", 1);	
		while (export[i][j])
		{
			ft_putchar_fd(export[i][j], 1);
			if (export[i][j] == '=')
			{
				ft_putchar_fd('"', 1);
				equ--;
			}
			j++;
		}
		if (!equ)
			ft_putchar_fd('"', 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

void	sort_env(void)
{
	char	**dup;
	char	*tmp;
	size_t	i;
	size_t	j;

	dup = _dup_env();
	i = 0;
	while (dup[i])	
	{
		j = i + 1;
		while (dup[j])
		{
			if (ft_strcmp(dup[i], dup[j]) > 0)
			{
				tmp = dup[i];
				dup[i] = dup[j];
				dup[j] = tmp;
			}
			j++;
		}
		i++;
	}
	_print_export(dup);
	ft_free_array(dup);
}
