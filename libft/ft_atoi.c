/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 11:10:16 by yviavant          #+#    #+#             */
/*   Updated: 2019/11/14 18:28:42 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	long	neg;
	long	sum;

	i = 0;
	neg = 1;
	sum = 0;
	while (str[i] == '\f' || str[i] == '\t' || str[i] == '\n'
	|| str[i] == '\r' || str[i] == '\v' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = (sum * 10) + (str[i] - 48);
		i++;
	}
	return (sum * neg);
}
