/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 18:02:07 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:57:00 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*s1_c;
	const unsigned char	*s2_c;

	i = 0;
	s1_c = (unsigned char *)s1;
	s2_c = (unsigned char *)s2;
	while (s1_c[i] != '\0' && s2_c[i] != '\0' && i < n)
	{
		if (s1_c[i] != s2_c[i])
			return (s1_c[i] - s2_c[i]);
		i++;
	}
	if (s1_c[i] != s2_c[i] && i != n)
		return (s1_c[i] - s2_c[i]);
	return (0);
}
