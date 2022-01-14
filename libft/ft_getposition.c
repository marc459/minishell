/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getposition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:24:06 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/23 14:40:50 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_getposition(char	*str, char c)
{
	size_t	i;

	if (!str)
		return (INT_MAX);
	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (i);
	return (INT_MAX);
}
