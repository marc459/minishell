/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trimchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 00:30:48 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/22 00:31:08 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_trimchar(char *str, char c)
{
	char	*final;
	size_t	i;
	size_t	j;
	size_t	trimed;

	final = calloc(sizeof(char), ft_strlen(str));
	if (!str || !final)
		return (NULL);
	i = -1;
	j = 0;
	trimed = 0;
	while (str[++i])
	{
		if ((str[i] != c) || (str[i] == c && trimed))
			final[j++] = str[i];
		else if (str[i] == c && !trimed)
			trimed = 1;
	}
	return (final);
}
