/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/01 14:55:53 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/08 21:38:24 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char	*big, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*loc;

	i = -1;
	j = 0;
	if (big == needle || ft_strlen(needle) == 0)
		return ((char *)big);
	loc = (char *)big;
	while (big[++i] && i < len)
	{
		while (needle[j] && needle[j] == big[i + j] && big[i + j]
			&& i + j < len)
			j++;
		if (needle[j] == '\0' && j <= len)
			return (loc += i);
		j = 0;
	}
	return (NULL);
}
