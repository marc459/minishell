/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 12:35:50 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/07 22:11:28 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*sourc;

	if (src == NULL && dst == NULL)
		return (NULL);
	dest = dst;
	sourc = src;
	i = -1;
	while (++i < n)
		dest[i] = sourc[i];
	return (dst);
}
