/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:22:44 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/27 10:54:26 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t len_needle;

	if (*needle == '\0')
		return ((char *)haystack);
	len_needle = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= len_needle)
	{
		if (*haystack == *needle
		&& ft_strncmp(haystack, needle, len_needle) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
