/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 18:05:55 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/25 11:19:53 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*n;
	size_t	i;
	size_t	len;

	if (!s1)
		return (NULL);
	i = -1;
	len = ft_strlen(s1);
	n = (char *)malloc(sizeof(char) * (len + 1));
	if (n == NULL)
		return (NULL);
	while (++i < len)
		n[i] = s1[i];
	n[i] = '\0';
	return (n);
}
