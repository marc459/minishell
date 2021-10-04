/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_integer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcos <marcos@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 15:12:20 by msantos-          #+#    #+#             */
/*   Updated: 2021/06/24 01:09:19 by marcos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	checkflags_minus_on_i(t_printf *f, int integer)
{
	if (f->width < 0)
		f->width = f->width * (-1);
	check_precisionflag_i(f, integer);
	if (integer < 0 && f->flag_precision == 0)
	{
		ft_putchar('-');
		f->len++;
	}
	ft_putstrcounter(ft_itoa_without_minus(integer), f);
	check_widthflag_i(f, integer);
	f->flag_precision = 1;
	check_zeroflag_i(f, integer);
}

void	checkflags_minus_off_i(t_printf *f, int integer)
{
	check_zeroflag_i(f, integer);
	check_widthflag_i(f, integer);
	check_precisionflag_i(f, integer);
	if (integer < 0 && f->flag_zero == 0 && f->flag_precision == 0)
	{
		ft_putchar('-');
		f->len++;
	}
	ft_putstrcounter(ft_itoa_without_minus(integer), f);
}

void	print_integer(t_printf *f)
{
	int integer;

	integer = va_arg(f->ap, int);
	if (f->flag_precision == 1 && f->precision == 0 && integer == 0)
	{
		if (f->width < 0)
			f->width = f->width * (-1);
		check_zeroflag_i(f, integer);
		check_widthflag_i(f, integer);
		if ((f->flag_width == 1 || f->flag_zero == 1) && f->width > 0)
		{
			ft_putchar(' ');
			f->len++;
		}
	}
	else if (f->flag_minus == 1 || f->width < 0)
		checkflags_minus_on_i(f, integer);
	else
		checkflags_minus_off_i(f, integer);
}
