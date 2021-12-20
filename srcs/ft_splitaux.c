/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitaux.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 19:07:59 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/20 19:21:24 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

size_t	ft_splitfindchar(char **split, char c)
{
	size_t	i;

	if (!split)
		return (0);
	i = -1;
	while (split[++i])
	{
		if (ft_findchar(split[i], c))
			return (1);
	}
	return (0);
}

char	**ft_splitdup(char **split)
{
	size_t	i;
	char	**splitdup;

	if (!split)
		return (NULL);
	splitdup = ft_calloc(sizeof(char *), ft_splitlen(split));
	if (!splitdup)
		return (NULL);
	i = -1;
	while (split[++i])
		splitdup = ft_strdup(split[i]);
	return (splitdup);
}
