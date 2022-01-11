/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_character.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgarcia <emgarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 17:22:34 by msantos-          #+#    #+#             */
/*   Updated: 2022/01/11 18:46:55 by emgarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	check_widthflag_c(t_printf *f)
{
	int	len;
	int	i;

	i = 0;
	if (f->flag_width == 1)
	{
		len = f->width - 1;
		while (i < len)
		{
			ft_putchar_fd(' ', f->fd);
			f->len++;
			i++;
		}
	}
}

void	print_character(t_printf *f)
{
	char	car;

	car = va_arg(f->ap, int);
	if (f->flag_minus == 1 || (f->width < 0 && f->flag_width == 1))
	{
		if (f->width < 0)
			f->width = f->width * (-1);
		ft_putchar_fd(car, f->fd);
		f->len++;
		check_widthflag_c(f);
	}
	else
	{
		check_widthflag_c(f);
		ft_putchar_fd(car, f->fd);
		f->len++;
	}
}
