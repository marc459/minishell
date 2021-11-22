/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revtrimchar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:32:24 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/22 00:38:29 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_revtrimchar(char *str, char c)
{
	char	*final;
	int		i;
	int		j;
	size_t	trimed;

	final = calloc(sizeof(char), ft_strlen(str));
	if (!str || !final)
		return (NULL);
	i = ft_strlen(str);
	j = ft_strlen(str) - 2;
	trimed = 0;
	while (--i > -1)
	{
		if ((str[i] != c) || (str[i] == c && trimed))
			final[j--] = str[i];
		else if (str[i] == c && !trimed)
			trimed = 1;
	}
	return (final);
}
