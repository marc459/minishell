/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitjoin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 15:51:36 by emgarcia          #+#    #+#             */
/*   Updated: 2021/11/21 16:28:40 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_splitjoin(char	**split, char cjoin)
{
	size_t	i;
	char	*join;
	char	*c;
	char	*aux;

	c = calloc(sizeof(char), 2);
	if (!split || !split[0] || !c)
		return (NULL);
	join = ft_strdup(split[0]);
	c[0] = cjoin;
	i = 0;
	while (split[++i])
	{
		aux = join;
		join = ft_strjoin(join, c);
		free(aux);
		aux = join;
		join = ft_strjoin(join, split[i]);
		free(aux);
	}
	free(c);
	return (join);
}
