/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bubblesort.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 15:02:15 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/11 17:45:29 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_bubble_sort(int *messy_nums, int length)
{
	int	c;
	int	d;
	int	swap;
	int	*ret;

	c = 0;
	d = 0;
	ret = (int *)malloc(sizeof(int) * length);
	ret = ft_intcpy(ret, messy_nums, length);
	while (c < length - 1)
	{
		while (d < length - c - 1)
		{
			if (ret[d] > ret[d + 1])
			{
				swap = ret[d];
				ret[d] = ret[d + 1];
				ret[d + 1] = swap;
			}
			d++;
		}
		c++;
		d = 0;
	}
	return (ret);
}
