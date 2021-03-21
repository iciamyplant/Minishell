/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:51:01 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 04:07:40 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_count_words_util(char const *s, t_split *sp)
{
	while (s[sp->i] && (s[sp->i] == '\'' || s[sp->i] == '"'))
	{
		while (s[sp->i] && s[sp->i] == '"')
			sp->i = protection(s, sp->i, '"', sp);
		while (s[sp->i] && s[sp->i] == '\'')
			sp->i = protection(s, sp->i, '\'', sp);
	}
	if (sp->i == sp->len)
		return (-1);
	if (s[sp->i] == '\\')
		sp->i++;
	return (0);
}

static int	ft_count_words(char const *s, char c, t_split *sp)
{
	sp->i = -1;
	sp->len = (int)ft_strlen(s);
	sp->count_words = 0;
	while (s[++sp->i])
	{
		if (ft_count_words_util(s, sp) == -1)
			break ;
		if (s[sp->i] && s[sp->i] == c && s[sp->i + 1] != c &&
			s[sp->i - 1] != '\\')
		{
			sp->j = sp->i + 1;
			while (s[sp->j] && sp->j == ' ')
				sp->j++;
			if (sp->j != (int)ft_strlen(s))
				sp->count_words++;
		}
		if (sp->i == sp->len)
			break ;
	}
	sp->count_words++;
	return (sp->count_words);
}

int			ft_malloc_words_util(char const *s, char c, t_split *sp)
{
	while (s[sp->j] == '\'' || s[sp->j] == '"')
	{
		while (s[sp->j] == '"')
			sp->j = protection(s, sp->j, '"', sp);
		while (s[sp->j] == '\'')
			sp->j = protection(s, sp->j, '\'', sp);
	}
	if (s[sp->j] && s[sp->j] == '\\')
	{
		sp->j++;
		sp->k++;
	}
	if ((s[sp->j] && s[sp->j] == '\0')
		|| (s[sp->j] == c && s[sp->j - 1] != '\\'))
		return (-1);
	return (0);
}

int			ft_malloc_words(char const *s, char **str,
			int words, t_split *sp)
{
	sp->i = -1;
	sp->j = -1;
	while (++sp->i < words)
	{
		sp->k = 0;
		while (s[++sp->j] && (s[sp->j] != sp->c || (s[sp->j] == sp->c
			&& (sp->j == 0 || s[sp->j - 1] == '\\'))))
		{
			if (ft_malloc_words_util(s, sp->c, sp) == -1)
				break ;
			sp->k++;
			if (sp->j == (int)ft_strlen(s))
				break ;
		}
		while (s[sp->j] && s[sp->j] == sp->c)
			sp->j++;
		sp->j--;
		if ((str[sp->i] = (char *)malloc(sizeof(char) * (sp->k + 1))) == NULL)
		{
			ft_leah_minishell(str, sp->i);
			return (0);
		}
	}
	return (1);
}

char		**ft_minishell_split(char const *s, char c)
{
	char	**str;
	int		count_words;
	t_split	split;

	count_words = 0;
	split.c = c;
	if (!s)
		return (NULL);
	count_words = ft_count_words(s, c, &split);
	if ((str = (char **)malloc(sizeof(char *) * (count_words + 1))) == NULL)
		return (NULL);
	if (!ft_malloc_words(s, str, count_words, &split))
		return (NULL);
	split.str = str;
	ft_write_words_minishell(s, count_words, &split);
	str[count_words] = 0;
	return (str);
}
