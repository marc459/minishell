/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 17:30:54 by emgarcia          #+#    #+#             */
/*   Updated: 2021/09/06 13:44:42 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_findchr(const char *str, char c)
{
	size_t	i;

	i = -1;
	while (str[++i] != '\0')
		if (str[i] == c)
			return (1);
	return (0);
}

static size_t	ft_contrem(char const *s1, char const *set)
{
	size_t	i;
	size_t	rem;
	size_t	len;

	i = -1;
	rem = 0;
	len = ft_strlen(s1);
	while (ft_findchr(set, s1[++i]) > 0 && s1[i] != '\0')
		rem++;
	if (rem == len)
		return (len);
	while (ft_findchr(set, s1[--len]) > 0 && len > 0)
		rem++;
	return (rem);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	len;
	size_t	rem;
	size_t	i;
	size_t	j;
	char	*final;

	if (!s1 || !set)
		return (NULL);
	rem = ft_contrem(s1, set);
	len = ft_strlen(s1);
	final = (char *)malloc(sizeof(char) * (len - rem + 1));
	if (final == NULL)
		return (NULL);
	i = 0;
	while (ft_findchr(set, s1[i]) > 0 && s1[i] != '\0')
		i++;
	j = len - rem + i;
	rem = i;
	while (i < j)
	{
		final[i - rem] = s1[i];
		i++;
	}
	final[i - rem] = '\0';
	return (final);
}
