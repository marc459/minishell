/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bidstrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:28:19 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/21 18:33:22 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_bidstrjoin(char **str, char **str2)
{
	char	**strcpy;
	int		x;
	int		y;

	if (!str)
		return (NULL);
	x = -1;
	y = -1;
	strcpy = (char **)malloc(sizeof(char *) * (ft_bidstrlen(str) + ft_bidstrlen(str2)));
	if (str == NULL)
		return (NULL);
	while (++x < ft_bidstrlen(str))
		strcpy[x] = ft_strdup(str[x]);
	while (++y < ft_bidstrlen(str))
		strcpy[x++] = ft_strdup(str[y]);
	return (strcpy);
}
