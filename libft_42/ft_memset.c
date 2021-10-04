/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:45:10 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:15:26 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memset(void *b, int c, size_t len)
{
	char		*charptr;
	size_t		i;

	charptr = (char *)b;
	i = 0;
	while (i < len)
	{
		charptr[i] = c;
		i++;
	}
	return ((char *)charptr);
}
