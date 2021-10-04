/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 13:24:11 by msantos-          #+#    #+#             */
/*   Updated: 2019/11/13 19:12:54 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memccpy(void *restrict dst, void *restrict src, int c, size_t n)
{
	size_t	i;
	char	*src_c;
	char	*dst_c;

	src_c = (char *)src;
	dst_c = (char *)dst;
	i = 0;
	while (i < n)
	{
		dst_c[i] = src_c[i];
		if (dst_c[i] == (char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
