/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:06:39 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/27 14:00:34 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_bzerognl(void *s)
{
	size_t	i;

	i = -1;
	while (++i < (BUFFER_SIZE + 1))
		((char *)s)[i] = '\0';
}

char	*ft_dropchar(char *str)
{
	size_t	i;
	char	*drop;

	if (!str)
		return (NULL);
	drop = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!drop)
		return (NULL);
	i = -1;
	while (str[++i])
		drop[i] = str[i];
	drop[i] = '\0';
	return (drop);
}

char	*ft_cutapend(int fd, ssize_t val, char *buf, char *line)
{
	char	*aux;
	char	*tmp;

	while (val == BUFFER_SIZE && !ft_findchar(buf, '\n'))
	{
		aux = line;
		line = ft_strjoin(line, buf);
		free(aux);
		ft_bzerognl(buf);
		val = read(fd, buf, BUFFER_SIZE);
	}
	aux = line;
	tmp = ft_cutstr(buf);
	line = ft_strjoin(line, tmp);
	free(tmp);
	free(aux);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buf = 0;
	char		*line;
	ssize_t		val;

	if (fd == -1)
		return (NULL);
	if (ft_findchar(buf, '\n'))
		return (ft_cutstr(buf));
	line = ft_dropchar(buf);
	if (!buf)
	{
		buf = malloc((sizeof(char) * (BUFFER_SIZE + 1)));
		if (!buf)
			return (NULL);
	}
	ft_bzerognl(buf);
	val = read(fd, buf, BUFFER_SIZE);
	if (val <= 0 && !ft_strlen(line))
	{
		free(line);
		free(buf);
		buf = 0;
		return (NULL);
	}
	return (ft_cutapend(fd, val, buf, line));
}
