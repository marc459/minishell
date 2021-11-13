/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/16 15:19:16 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/26 17:09:04 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_findchar(char *str, char c)
{
	size_t	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

size_t	ft_countcut(char *str)
{
	size_t	i;
	size_t	before;

	if (!str)
		return (0);
	i = -1;
	before = 1;
	while (str[++i] && before)
	{
		if (str[i] == '\n')
			before--;
	}
	return (i);
}

char	*ft_cutstr(char *str)
{
	char	*cut;
	size_t	sizecut;
	size_t	i;

	cut = malloc(sizeof(char) * (ft_countcut(str) + 1));
	if (!cut)
		return (NULL);
	i = -1;
	while (str[++i])
		if (i < ft_countcut(str))
			cut[i] = str[i];
	cut[ft_countcut(str)] = '\0';
	sizecut = ft_countcut(str);
	i = 0;
	while (str[sizecut + i])
	{
		str[i] = str[sizecut + i];
		i++;
	}
	while (str[i])
		str[i++] = '\0';
	return (cut);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*final;

	if (!s1 && !s2)
		return (NULL);
	i = -1;
	j = -1;
	final = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (final == NULL)
		return (NULL);
	if (!s1)
		i = 0;
	while (s1 && s1[++i] != '\0')
		final[i] = s1[i];
	if (!s2)
		j = 0;
	while (s2 && s2[++j] != '\0')
		final[i + j] = s2[j];
	final[i + j] = '\0';
	return (final);
}
