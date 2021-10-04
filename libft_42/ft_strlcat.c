/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:34:57 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:17:11 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	rsl;

	i = ft_strlen(dst);
	rsl = ft_strlen(src);
	j = 0;
	if (dstsize == 0)
		return (rsl);
	if (dstsize < i)
	{
		rsl += dstsize;
	}
	else
	{
		rsl += i;
		while (src[j] != '\0' && i < dstsize - 1 && dst != src)
		{
			dst[i] = src[j];
			j++;
			i++;
		}
		dst[i] = '\0';
	}
	return (rsl);
}
