/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_charxtimes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 17:53:24 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/11 18:48:05 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_print_charxtimes(t_printf *f, char c, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		write(1, &c, 1);
		f->len++;
		i++;
	}
}
