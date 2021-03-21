/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_char_by_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 09:54:26 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/26 15:52:37 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_get_char_by_index(char *str, char c)
{
	char	*ch;

	ch = ft_strchr(str, c);
	if (!ch)
		return (-1);
	return ((size_t)(ch - str));
}
