/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 15:28:03 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/08 21:17:15 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*aux;

	if (c > 256)
		c %= 256;
	aux = NULL;
	while (*s != '\0')
	{
		if (*s == c)
			aux = (char *)s;
		s++;
	}
	if (*s == c)
		aux = (char *)s;
	return (aux);
}
