/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 19:24:00 by emgarcia          #+#    #+#             */
/*   Updated: 2021/09/03 19:24:04 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(char const *s, size_t *i, char c)
{
	size_t	cont_str;
	size_t	find_let;

	cont_str = 0;
	find_let = 0;
	while (s[++*i] != '\0')
	{
		if ((s[*i] == c) && (*i > 0) && (find_let > 0))
		{
			cont_str++;
			find_let = 0;
		}
		else if (s[*i] != c)
			find_let++;
	}
	if (find_let > 0)
		cont_str++;
	return (cont_str);
}

static char	**ft_fill_split(char **split, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	palabra;

	i = -1;
	j = 0;
	k = 0;
	palabra = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != c)
		{
			palabra++;
			split[j][k++] = s[i];
		}
		else if (palabra > 0)
		{
			split[j++][k] = '\0';
			k = 0;
			palabra = 0;
		}
	}
	return (split);
}

static void	ft_asign(size_t *i, size_t *j, size_t a, size_t b)
{
	*i = a;
	*j = b;
}

char	**ft_split(char const *s, char c)
{
	size_t	index[3];
	size_t	cont_str;
	char	**split;

	if (!s)
		return (NULL);
	ft_asign(&index[0], &index[1], -1, 0);
	split = ft_calloc((ft_count_words(s, &index[0], c) + 1), sizeof(char *));
	ft_asign(&index[2], &index[0], index[0] + 1, -1);
	if (!split)
		return (NULL);
	cont_str = 0;
	while (++index[0] < index[2])
	{
		if (s[index[0]] != c && s[index[0]] != '\0')
			cont_str++;
		else
		{
			if (cont_str > 0)
				split[index[1]++] = ft_calloc((cont_str + 1), sizeof(char));
			cont_str = 0;
		}
	}
	return (ft_fill_split(split, s, c));
}
