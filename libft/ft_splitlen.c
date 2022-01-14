/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 23:20:51 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/24 23:22:40 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_splitlen(char **split)
{
	size_t	i;

	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	return (i);
}
