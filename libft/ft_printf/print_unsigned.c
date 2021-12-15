/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 18:43:53 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/24 01:10:10 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	checkflags_minus_on_u(t_printf *f, unsigned int integer)
{
	if (f->width < 0)
		f->width = f->width * (-1);
	check_precisionflag_u(f, integer);
	ft_putstrcounter(ft_itoa_without_minus(integer), f);
	check_widthflag_u(f, integer);
	f->flag_precision = 1;
	check_zeroflag_u(f, integer);
}

void	checkflags_minus_off_u(t_printf *f, unsigned int integer)
{
	check_zeroflag_u(f, integer);
	check_widthflag_u(f, integer);
	check_precisionflag_u(f, integer);
	ft_putstrcounter(ft_itoa_without_minus(integer), f);
}

void	print_unsigned(t_printf *f)
{
	unsigned int integer;

	integer = va_arg(f->ap, unsigned int);
	if (f->flag_precision == 1 && f->precision == 0 && integer == 0)
	{
		if (f->width < 0)
			f->width = f->width * (-1);
		check_zeroflag_u(f, integer);
		check_widthflag_u(f, integer);
		if ((f->flag_width == 1 || f->flag_zero == 1) && f->width > 0)
		{
			ft_putchar(' ');
			f->len++;
		}
	}
	else if (f->flag_minus == 1 || f->width < 0)
		checkflags_minus_on_u(f, integer);
	else
		checkflags_minus_off_u(f, integer);
}
