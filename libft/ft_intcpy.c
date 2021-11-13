/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 20:01:27 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/10 20:11:22 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_intcpy(int *dst, int *src, size_t n)
{
	size_t	i;
	int		*src_c;
	int		*dst_c;

	src_c = src;
	dst_c = dst;
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
