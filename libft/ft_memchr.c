/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 04:56:39 by yviavant          #+#    #+#             */
/*   Updated: 2020/01/07 18:58:16 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_s;

	ptr_s = (unsigned char *)s;
	while (n--)
	{
		if (*ptr_s == (unsigned char)c)
			return (ptr_s);
		ptr_s++;
	}
	return (NULL);
}
