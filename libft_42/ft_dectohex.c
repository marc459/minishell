/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dectohex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:55:11 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/09 17:32:30 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dectohex(long long num)
{
	int		rem;
	int		i;
	char	hex[100];

	rem = 0;
	i = 0;
	if (num == 0)
	{
		hex[0] = '0';
		hex[1] = '0';
		i = i + 2;
	}
	while (num > 0)
	{
		rem = num % 16;
		if (rem < 10)
			hex[i] = (char)rem + 48;
		else
			hex[i] = (char)rem + 55;
		num /= 16;
		i++;
	}
	hex[i] = '\0';
	return (ft_strdup(ft_strrev(hex)));
}
