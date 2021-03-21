/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:51:01 by yviavant          #+#    #+#             */
/*   Updated: 2021/03/20 04:01:01 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void			ft_leah_minishell(char **str, int index)
{
	while (index)
	{
		free(str[index]);
		index--;
	}
	free(str);
}

int				protection(char const *s, int i, char c, t_split *split)
{
	i++;
	while (s[i] && s[i] != c)
	{
		if (s[i] == '\\')
		{
			i++;
			split->k++;
		}
		split->k++;
		i++;
	}
	if (i == (int)ft_strlen(s))
		return (i);
	i++;
	split->k = split->k + 2;
	return (i);
}

void			ft_write_words_util(char const *s, t_split *sp)
{
	char	quote;

	while (s[sp->j] && (s[sp->j] == '\'' || s[sp->j] == '"'))
	{
		quote = s[sp->j];
		sp->str[sp->i][sp->k++] = s[sp->j++];
		while (s[sp->j] && s[sp->j] != quote)
		{
			if (s[sp->j] == '\\')
				sp->str[sp->i][sp->k++] = s[sp->j++];
			if (sp->j == (int)ft_strlen(s))
				return ;
			sp->str[sp->i][sp->k++] = s[sp->j++];
		}
		if (sp->j == (int)ft_strlen(s))
			return ;
		sp->str[sp->i][sp->k++] = s[sp->j++];
	}
	if (s[sp->j] == '\\')
		sp->str[sp->i][sp->k++] = s[sp->j++];
}

void			ft_write_words_minishell(char const *s, int words, t_split *sp)
{
	sp->i = -1;
	sp->j = 0;
	while (s && s[sp->j] && ++sp->i < words)
	{
		sp->k = 0;
		while (s[sp->j] && s[sp->j] == sp->c)
			sp->j++;
		while ((s[sp->j] && (s[sp->j] != sp->c
			|| (s[sp->j] == sp->c && sp->j > 0
			&& s[sp->j - 1] == '\\'))))
		{
			ft_write_words_util(s, sp);
			if (sp->j && s[sp->j - 1] != '\\' && (s[sp->j] == sp->c
				|| s[sp->j] == '\0'))
				break ;
			if (sp->j == (int)ft_strlen(s))
				break ;
			sp->str[sp->i][sp->k++] = s[sp->j++];
		}
		sp->str[sp->i][sp->k] = '\0';
	}
}
