/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:44:23 by yviavant          #+#    #+#             */
/*   Updated: 2020/02/10 14:24:10 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	size;

	count = 0;
	size = 0;
	if (!dst)
		return (0);
	size = ft_strlen(src);
	if (!dstsize)
		return (size);
	while (src[count] && count < dstsize - 1)
	{
		dst[count] = src[count];
		count++;
	}
	dst[count] = '\0';
	return (size);
}
