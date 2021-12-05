/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 19:47:54 by emgarcia          #+#    #+#             */
/*   Updated: 2021/12/04 22:19:12 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsort(char **split)
{
	char	**sort;
	size_t	i;
	size_t	j;
	size_t	cont;

	if (!split)
		return (NULL);
	sort = calloc(sizeof(char *), (ft_splitlen(split) + 1));
	if (!sort)
		return (NULL);
	i = -1;
	while (++i < ft_splitlen(split))
	{
		j = -1;
		cont = 0;
		while (++j < ft_splitlen(split))
			if (ft_strncmp(split[i], split[j], ft_strlen(split[i])) > 0)
				cont++;
		sort[cont] = ft_strdup(split[i]);
	}
	return (sort);
}
