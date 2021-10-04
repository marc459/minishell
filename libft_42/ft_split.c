/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 18:54:35 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/10 18:51:12 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wordcount(char const *s, char c)
{
	int	i;
	int	x;
	int	slen;

	i = 0;
	i = 0;
	x = 0;
	slen = ft_strlen(s);
	while (s[i] == c)
		i++;
	while (i <= slen)
	{
		if ((s[i] == c) && (s[i - 1] != c))
			x++;
		if ((s[i] == '\0') && (s[i - 1] != c))
			x++;
		i++;
	}
	return (x);
}

int	checkblanks(char const *s, char c)
{
	int	i;
	int	blanks;

	i = 0;
	blanks = 1;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			blanks = 0;
		i++;
	}
	return (blanks);
}

char	**create_bidimensional(const char *s, char **str, char c, size_t i)
{
	size_t	y;
	size_t	x;
	size_t	z;

	y = -1;
	x = 0;
	z = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && s[i] != '\0')
			x++;
		else if ((s[i] == c || s[i] == '\0') && (x > 0))
		{
			str[z] = (char *)ft_calloc(sizeof(char), (x + 1));
			while (++y < x)
				str[z][y] = s[i + y - x];
			str[z++][y] = '\0';
			x = 0;
			y = -1;
		}
		i++;
	}
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	x;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (checkblanks(s, c) == 1 || s[0] == '\0')
	{
		str = ft_calloc(sizeof(char *), 1);
		return (str);
	}
	x = wordcount(s, c);
	str = (char **)ft_calloc(sizeof(char *), (x + 1));
	if (!str)
		return (NULL);
	str[x] = NULL;
	while (s[i] == c)
		i++;
	return (create_bidimensional(s, str, c, i));
}
