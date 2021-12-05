/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 20:20:19 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/04 20:23:37 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_splitdup(char **split)
{
	size_t	i;
	char	**dup;

	if (!split)
		return (NULL);
	dup = calloc(sizeof(char *), (ft_splitlen(split) + 1));
	if (!dup)
		return (NULL);
	i = -1;
	while (++i < ft_splitlen(split))
		dup[i] = ft_strdup(split[i]);
	return (dup);
}
