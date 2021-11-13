/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 17:05:23 by emgarcia          #+#    #+#             */
/*   Updated: 2021/08/08 14:34:42 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		number;
	int		signo;
	size_t	datos;

	i = 0;
	datos = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == ' ')
		i++;
	signo = 1;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			signo *= (-1);
	number = 0;
	i--;
	while (str[++i] >= '0' && str[i] <= '9' && ++datos)
		number = 10 * number + str[i] - '0';
	if (datos > 18 && signo < 0)
		return (0);
	else if (datos > 18)
		return (-1);
	number *= signo;
	return (number);
}
