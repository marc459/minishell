/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 12:55:36 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:17:18 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	count;
	size_t	i;

	count = 0;
	if (dst == NULL)
		return (dstsize);
	while (src[count] != '\0')
		++count;
	i = 0;
	if (dstsize > 0)
	{
		while (src[i] != '\0' && i < (dstsize - 1))
		{
			dst[i] = src[i];
			++i;
		}
		dst[i] = '\0';
	}
	return (count);
}
