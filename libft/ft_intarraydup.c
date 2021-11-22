/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intarraydup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 10:27:40 by msantos-          #+#    #+#             */
/*   Updated: 2021/11/08 20:41:14 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_intarraydup(int *n1)
{
	int	i;
	int	*ret;

	i = ft_len((long)n1);
	if (!i)
		return (NULL);
	ret = (int *)malloc(sizeof(int) * i);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, n1, i);
	return (ret);
}
