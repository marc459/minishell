/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bintodec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:54:18 by msantos-          #+#    #+#             */
/*   Updated: 2021/07/15 15:56:51 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_bintodec(long long n)
{
	int	dec;
	int	i;
	int	rem;
	int	poww;

	i = 0;
	dec = 0;
	poww = 1;
	while (n != 0)
	{
		rem = n % 10;
		n /= 10;
		dec += rem * poww;
		poww = 2 * poww;
		++i;
	}
	return (dec);
}
