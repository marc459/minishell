/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 13:07:53 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/07 22:14:19 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*s_dst;
	char	*s_src;

	if (src == NULL && dst == NULL)
		return (NULL);
	s_dst = (char *)dst;
	s_src = (char *)src;
	if (s_dst > s_src && (s_src + len > s_dst))
	{
		s_dst = s_dst + len - 1;
		s_src = s_src + len - 1;
		while (len--)
			*s_dst-- = *s_src--;
	}
	else
		while (len--)
			*s_dst++ = *s_src++;
	return (dst);
}
