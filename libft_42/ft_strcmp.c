/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 14:09:25 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:16:43 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const void *s1, const void *s2)
{
	char	*t1;
	char	*t2;
	int		i;

	t1 = (char *)s1;
	t2 = (char *)s2;
	i = 0;
	while (t1[i] || t2[i])
	{
		if (t1[i] != t2[i])
			return (0);
		i++;
	}
	return (1);
}
