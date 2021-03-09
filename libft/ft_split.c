/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 23:51:01 by yviavant          #+#    #+#             */
/*   Updated: 2020/10/28 16:08:13 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_leah(char **str, int index)
{
	while (index)
	{
		free(str[index]);
		index--;
	}
	free(str);
}

static int	ft_count_words(char const *s, char c)
{
	int		i;
	int		count_words;

	i = -1;
	count_words = 0;
	while (s[++i])
		if ((s[i + 1] == c || s[i + 1] == '\0') && s[i] != c)
			count_words++;
	return (count_words);
}

static void	ft_write_words(char const *s, char c, char **str, int words)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	while ((i++) < words)
	{
		k = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
			str[i][k++] = s[j++];
		str[i][k] = '\0';
	}
}

static int	ft_malloc_words(char const *s, char c, char **str, int words)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	while ((i++) < words)
	{
		k = 0;
		while (s[j] && s[j] == c)
			j++;
		while (s[j] && s[j] != c)
		{
			j++;
			k++;
		}
		if ((str[i] = (char *)malloc(sizeof(char) * (k + 1))) == NULL)
		{
			ft_leah(str, i);
			return (0);
		}
	}
	return (1);
}

char		**ft_split(char const *s, char c)
{
	char	**str;
	int		count_words;

	if (!s)
		return (NULL);
	count_words = ft_count_words(s, c);
	if ((str = (char **)malloc(sizeof(char *) * (count_words + 1))) == NULL)
		return (NULL);
	if (!ft_malloc_words(s, c, str, count_words))
		return (NULL);
	ft_write_words(s, c, str, count_words);
	str[count_words] = 0;
	return (str);
}