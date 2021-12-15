/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_zero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:22:43 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 20:26:47 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	check_zeroflag_i(t_printf *f, int integer)
{
	int len;
	int tmp;

	tmp = 0;
	if (f->flag_precision == 1 && f->flag_zero == 1)
	{
		if (f->flag_precision)
			tmp = f->precision - ft_intlen(integer);
		tmp = (tmp < 0) ? 0 : tmp;
		len = f->width - ft_intlen(integer) - (tmp);
		if (integer < 0)
			len--;
		ft_print_charxtimes(f, ' ', len);
	}
	else if (f->flag_zero == 1)
	{
		len = f->width - ft_intlen(integer);
		if (integer < 0)
		{
			len--;
			ft_putchar('-');
			f->len++;
		}
		ft_print_charxtimes(f, '0', len);
	}
}

void	check_zeroflag_p(t_printf *f, char *str)
{
	int len;
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	if (f->flag_precision == 1 && f->flag_zero == 1 && f->flag_minus == 0)
	{
		if (f->flag_precision)
			tmp = f->precision - ft_strlen(str);
		if (tmp < 0)
			tmp = 0;
		len = f->width - ft_strlen(str) - (tmp);
		ft_print_charxtimes(f, ' ', len);
	}
	else if (f->flag_zero == 1)
	{
		len = f->width - ft_strlen(str);
		ft_print_charxtimes(f, '0', len);
	}
}

void	check_zeroflag_u(t_printf *f, long int integer)
{
	int len;
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	if (f->flag_precision == 1 && f->flag_zero == 1)
	{
		if (f->flag_precision)
			tmp = f->precision - ft_intlen(integer);
		if (tmp < 0)
			tmp = 0;
		len = f->width - ft_intlen(integer) - (tmp);
		if (integer < 0)
			len--;
		ft_print_charxtimes(f, ' ', len);
	}
	else if (f->flag_zero == 1)
	{
		len = f->width - ft_intlen(integer);
		ft_print_charxtimes(f, '0', len);
	}
}

void	check_zeroflag_x(t_printf *f, char *str)
{
	int len;
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	if (f->flag_precision == 1 && f->flag_zero == 1)
	{
		if (f->flag_precision)
			tmp = f->precision - ft_strlen(str);
		if (tmp < 0)
			tmp = 0;
		len = f->width - ft_strlen(str) - (tmp);
		ft_print_charxtimes(f, ' ', len);
	}
	else if (f->flag_zero == 1)
	{
		len = f->width - ft_strlen(str);
		ft_print_charxtimes(f, '0', len);
	}
}
