/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_width.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:04:33 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 20:28:09 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	check_widthflag_i(t_printf *f, int integer)
{
	int len;
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	if (f->flag_width == 1)
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
}

void	check_widthflag_s(t_printf *f, char *str)
{
	int len;
	int tmp;

	tmp = 0;
	if (f->flag_width == 1)
	{
		if (f->flag_precision)
			tmp = f->precision - ft_strlen(str);
		if (tmp < 0)
			tmp = 0;
		len = f->width - ft_strlen(str) - (tmp);
		ft_print_charxtimes(f, ' ', len);
	}
}

void	check_widthflag_p(t_printf *f, char *str)
{
	int len;
	int tmp;

	tmp = 0;
	if (f->flag_width == 1)
	{
		if (f->flag_precision)
			tmp = f->precision - ft_strlen(str);
		if (tmp < 0)
			tmp = 0;
		len = f->width - ft_strlen(str) - (tmp) - 2;
		ft_print_charxtimes(f, ' ', len);
	}
}

void	check_widthflag_u(t_printf *f, long int integer)
{
	int len;
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	if (f->flag_width == 1)
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
}

void	check_widthflag_x(t_printf *f, char *str)
{
	int len;
	int i;
	int tmp;

	i = 0;
	tmp = 0;
	if (f->flag_width == 1)
	{
		if (f->flag_precision)
			tmp = f->precision - ft_strlen(str);
		if (tmp < 0)
			tmp = 0;
		len = f->width - ft_strlen(str) - (tmp);
		while (i < len)
		{
			ft_putchar(' ');
			f->len++;
			i++;
		}
	}
}
