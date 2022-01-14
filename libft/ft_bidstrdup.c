/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bidstrdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 18:30:12 by msantos-          #+#    #+#             */
/*   Updated: 2021/12/21 18:33:13 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_bidstrdup(char **str)
{
	char	**strcpy;
	int		x;

	if (!str)
		return (NULL);
	x = -1;
	strcpy = (char **)malloc(sizeof(char *) * ft_bidstrlen(str));
	if (str == NULL)
		return (NULL);
	while (++x < ft_bidstrlen(str))
		strcpy[x] = ft_strdup(str[x]);
	return (strcpy);
}
