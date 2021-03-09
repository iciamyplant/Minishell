/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 21:44:12 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/13 14:09:09 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_set(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int		ft_count_set(char const *str, char const *set, int after)
{
	int		i;
	int		count_set;

	if (after)
		i = 0;
	else
		i = (int)ft_strlen(str) - 1;
	count_set = 0;
	while (str[i])
	{
		if (ft_is_set(str[i], set))
			count_set++;
		else
			return (count_set);
		if (after)
			i++;
		else
			i--;
	}
	return (count_set);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		len_s1;
	int		count_a;
	int		count_b;

	if (!s1 || !set)
		return (NULL);
	len_s1 = (int)ft_strlen(s1) - 1;
	count_a = ft_count_set(s1, set, 1);
	if (count_a == len_s1 + 1)
		return (ft_strdup(""));
	count_b = ft_count_set(s1, set, 0);
	str = ft_substr(s1, (unsigned int)count_a
	, (size_t)(len_s1 - (count_b + count_a) + 1));
	return (str);
}
