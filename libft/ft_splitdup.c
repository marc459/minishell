/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 20:20:19 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/21 12:18:51 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitdup(char **split)
{
	size_t	i;
	char	**dup;

	if (!split)
		return (NULL);
	dup = ft_calloc(sizeof(char *), (ft_splitlen(split) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (split[++i])
		dup[i] = ft_strdup(split[i]);
	return (dup);
}
