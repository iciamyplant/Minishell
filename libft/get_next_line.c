/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yviavant <yviavant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:02:45 by yviavant          #+#    #+#             */
/*   Updated: 2020/02/04 13:43:38 by yviavant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int		ft_free(char **str, char *buf, int ret)
{
	if (*str && (ret == -1 || ret == 0))
	{
		free(*str);
		*str = NULL;
	}
	if (buf)
		free(buf);
	return (ret);
}

static int		ft_check(char **str, char **line)
{
	char	*tmp;
	int		i;

	i = -1;
	while ((*str)[++i])
		if ((*str)[i] == '\n')
		{
			if (i == 0)
			{
				if (!(*line = ft_strdup("")))
					return (-1);
			}
			else if (!(*line = ft_substr(*str, 0, i)))
				return (-1);
			tmp = *str;
			if (!(*str = ft_substr(*str, (i + 1), ft_strlen(*str))))
				return (-1);
			free(tmp);
			return (1);
		}
	return (0);
}

static int		ft_read(int fd, char *buf, char **str, char **line)
{
	int		bytes;
	char	*tmp;

	if ((bytes = (ft_check(str, line))) == -1)
		return (ft_free(str, buf, -1));
	if (bytes)
		return (ft_free(str, buf, 1));
	while ((bytes = read(fd, buf, BUFFER_SIZE)) >= 0)
	{
		buf[bytes] = '\0';
		if (buf[0] == '\0' && ft_strlen(*str))
			continue;
		else if (buf[0] == '\0' && ft_strlen(*str) <= 0)
			return (ft_free(str, buf, 0));
		tmp = *str;
		*str = ft_strjoin(*str, buf);
		free(tmp);
		if ((bytes = ft_check(str, line)) == -1)
			return (ft_free(str, buf, -1));
		if (bytes)
			return (ft_free(str, buf, 1));
	}
	if (bytes == -1 || !(*line = ft_substr(*str, 0, ft_strlen(*str))))
		return (ft_free(str, buf, -1));
	return (ft_free(str, buf, 0));
}

int				get_next_line(int fd, char **line)
{
	static char *str;
	char		*buf;

	if (fd < 0 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (!str)
		if (!(str = ft_calloc(1, sizeof(char))))
			return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (ft_free(&str, buf, -1));
	return (ft_read(fd, buf, &str, line));
}
