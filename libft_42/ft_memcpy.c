/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:08:02 by msantos-          #+#    #+#             */
/*   Updated: 2021/05/28 12:13:40 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t	i;
	char	*src_c;
	char	*dst_c;

	src_c = (char *)src;
	dst_c = (char *)dst;
	i = 0;
	if (!n || dst == src)
		return (dst);
	while (i < n)
	{
		dst_c[i] = src_c[i];
		i++;
	}
	return (dst);
}
